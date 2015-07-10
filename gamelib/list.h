#ifndef GLIB_ARRAY_H
#define GLIB_ARRAY_H

#include "string.h"
#include "log.h"

namespace glib {
	//-----------------------------------------
	// glib::InvalidListOperationException
	//-----------------------------------------
	class InvalidListOperationException {
	public:
		enum ExceptionClass { E_CANNOT_RESIZE_STATIC_LIST, E_OUT_OF_MEMORY };

		InvalidListOperationException( ExceptionClass exceptionClass, const String & message ):
			m_message( message ),
			m_class( exceptionClass ) {
			Error( "Cannot grow a static list!\n" );
		}

		InvalidListOperationException( const InvalidListOperationException & o ) :
			m_message( o.m_message ),
			m_class( o.m_class ) {}

		const String & GetMessage() const { return m_message; }
		ExceptionClass GetClass() const { return m_class; }

	private:
		String			m_message;
		ExceptionClass	m_class;
	};

	//-----------------------------------------
	// glib::List
	//-----------------------------------------
	// Need functions for: Sort, Slice, Find
	template< typename _elementType  >
	class List {
	public:
		//-----------------------------------------
		List(): 
			m_allocCount( 0 ),
			m_ptr( nullptr ),
			m_itemCount( 0 ),
			m_isStatic( false ) {
		}

		//-----------------------------------------
		// Copy Constructor
		explicit List( const List< _elementType > & other ):
			m_allocCount( other.m_allocCount ),
			m_itemCount( other.m_itemCount ) {
				m_ptr = new _elementType[ m_allocCount ];

				for ( uint i = 0; i < m_itemCount; ++i ) {
					m_ptr[ i ] = other.m_ptr[ i ];
				}
		}

		//-----------------------------------------
		// ~List()
		~List() {
			if ( !m_isStatic && m_ptr != nullptr ) {
				delete[] m_ptr;
			}
		}

		//-----------------------------------------
		// NextSize
		inline uint NextSize() const {
			return m_allocCount == 0 ? 1 : m_allocCount << 1;
		}

		//-----------------------------------------
		// Remove
		void Pop() {
			m_ptr[ --m_itemCount ].~_elementType();
		}

		//-----------------------------------------
		// Top
		const _elementType & Top() const {
			return m_ptr[ m_itemCount - 1 ];
		}

		//-----------------------------------------
		// Push
		inline void Push( const _elementType & item ) {
			Append( item );
		}

		//-----------------------------------------
		// Remove
		void Remove( const uint index ) {
			glibAssert( index >= 0 && index < m_itemCount );

			// special case - "pop"
			if (index == m_itemCount - 1) {
				Pop();
				return;
			}

			// Move everything down.
			for (uint i = index; i < m_itemCount - 1; ++i) {
				m_ptr[ i ].~_elementType();
				m_ptr[ i ] = m_ptr[ i + 1 ];
			}

			--m_itemCount;
		}

		//-----------------------------------------
		// operator []
		_elementType & operator [] ( uint index ) {
			glibAssert( index < m_itemCount );
			return m_ptr[ index ];
		}

		//-----------------------------------------
		// operator =
		void operator = ( const List< _elementType > & rhs ) {
			// Free the current list.
			if ( rhs.m_itemCount > this->m_itemCount ) {
				delete[] m_ptr;

				m_allocCount = rhs->m_itemCount;
				m_itemCount = m_allocCount;
				m_ptr = new _elementType[ m_allocCount ];
			} else {
				for ( uint i = 0; i < m_itemCount ) {
					m_ptr[ i ].~_elementType();
				}

				m_itemCount = other.m_itemCount;
			}

			for ( uint i = 0; i < m_itemCount; ++i ) {
				m_ptr[ i ] = other.m_ptr[ i ];
			}

		}

		//-----------------------------------------
		// Count
		inline uint Count() const { return m_itemCount; }

		//-----------------------------------------
		// Append
		// Can throw - glib::InvalidListOperationException
		void Append( const _elementType & item ) {
			if ( m_allocCount <= m_itemCount ) {
				if ( m_isStatic ) {
					throw InvalidListOperationException( InvalidListOperationException::ExceptionClass::E_CANNOT_RESIZE_STATIC_LIST, "String.Append() - cannot resize static list" );
				}

				m_allocCount = NextSize();

				// PERF FIXME: THIS CAN BE VERY EXPENSIVE(!) BOTH IN CPU AND MEMORY since it calls the default constructors on all the objects in this list.
				// Recommend allocating a (raw) buffer, and calling placement new on each member of it.
				auto newPtr = new _elementType[ m_allocCount ];
				for ( uint i = 0; i < m_itemCount; ++i ) {
					newPtr[i] = m_ptr[i];
				}

				delete[] m_ptr;
				m_ptr = newPtr;
			}

			m_ptr[ m_itemCount++ ] = item;
		}

	protected:
		uint				m_allocCount;
		_elementType	*	m_ptr;
		uint				m_itemCount;
		bool				m_isStatic;

		// Initialize from a static list.
		List( int _size, _elementType * _ptr ): 
			m_allocCount( _size ),
			m_ptr( _ptr ),
			m_itemCount( 0 ), 
			m_isStatic( true ) { }
	};

	//-----------------------------------------
	// glib::StaticList
	//-----------------------------------------
	// This list is statically allocated, and therefore can be a better option when we need a non-resizeable list, because the memory is owned by the owner of the object.
	// Which can be the stack, or another object instead of the heap.
	template < typename _elementType, int _size >
	class StaticList: public List< _elementType > {
	public:
		StaticList() : List( _size, m_list ) {}
	private:
		_elementType m_list[ _size ];
	};

}	// namespace glib

#endif // GLIB_ARRAY_H