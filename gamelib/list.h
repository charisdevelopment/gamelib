#ifndef GLIB_ARRAY_H
#define GLIB_ARRAY_H

namespace glib {
	//=========================================
	// GlibList
	//=========================================
	template <typename T >
	class GLibList {
	public:
		//======================================
		GLibList() : m_ptr(nullptr),
			m_itemCount(0),
			m_allocCount(0) {
		}

		//======================================
		~GLibList() {
			if (m_ptr != nullptr) {
				delete[] m_ptr;
			}
		}

		//======================================
		// NextSize
		//======================================
		inline uint NextSize() {
			return m_allocCount == 0 ? 1 : m_allocCount << 1;
		}

		//======================================
		// Remove
		//======================================
		void Pop() {
			m_ptr[ --m_itemCount ].~T();
		}

		//======================================
		// Top
		//======================================
		const T & Top() {
			return m_ptr[ m_itemCount - 1 ];
		}

		//======================================
		// Push
		//======================================
		inline void Push(const T & item) {
			Append( item );
		}

		//======================================
		// Remove
		//======================================
		void Remove( const uint index ) {
			glibassert( index >= 0 && index < m_itemCount );

			// special case - "pop"
			if (index == m_itemCount - 1) {
				Pop();
				return;
			}

			// Move everything down.
			for (auto i = index; i < m_itemCount - 1; ++i) {
				m_ptr[ i ].~T();
				m_ptr[ i ] = m_ptr[ i + 1 ];
			}

			--m_itemCount;
		}

		//======================================
		// Append
		//======================================
		void Append( const T & item ) {
			if ( m_allocCount <= m_itemCount ) {
				// resize the array
				m_allocCount = NextSize();

				auto newPtr = new T[ m_allocCount ];
				for ( auto i = 0U; i < m_itemCount; ++i) {
					newPtr[i] = m_ptr[i];
				}

				// Free/Swap contents.
				delete[] m_ptr;
				m_ptr = newPtr;
			}

			m_ptr[ m_itemCount++ ] = item;
		}

		//======================================
		// [] operator
		//======================================
		T & operator [] (uint index) {
			glibassert(index < m_itemCount);
			return m_ptr[index];
		}

		inline uint Count() { return m_itemCount; }

	private:
		T	*	m_ptr;
		uint	m_itemCount;
		uint	m_allocCount;
	};

}	// namespace glib

#endif // GLIB_ARRAY_H