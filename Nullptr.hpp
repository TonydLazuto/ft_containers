
namespace ft 
{
	static class nullptr_t
	{
		public:

			template<class T>
			operator T*() const { return (0); }

			template<class C, class T>
			operator T C::*() const { return (0); }

		private:

			void operator&() const;

	} u_nullptr = {};
}
