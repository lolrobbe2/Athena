#pragma once
#ifndef BUFFER
#define BUFFER
#include <vector>
#include <type_traits>

namespace athena
{
    class buffer;
    // Trait to check if T has a member function serialize with the given signature
    template <typename T>
    struct has_serialize_method
    {
    private:
        // Helper template to check if the serialize method exists and has the correct signature
        template <typename U>
        static auto test(int) -> decltype(std::declval<U>().serialize(std::declval<athena::buffer*>(), std::declval<const U&>()), void(), std::true_type{});

        template <typename>
        static std::false_type test(...);

    public:
        using type = decltype(test<T>(0));
        static constexpr bool value = type::value;
    };

    template <typename T>
    struct has_deserialize_method
    {
    private:
        // Helper template to check if the serialize method exists and has the correct signature
        template <typename U>
        static auto test(int) -> decltype(std::declval<U>().deserialize(std::declval<athena::buffer*>()), std::declval<U&>(), std::true_type{});

        template <typename>
        static std::false_type test(...);

    public:
        using type = decltype(test<T>(0));
        static constexpr bool value = type::value;
    };

	class buffer 
	{
	public:
#pragma region write
		void writeData(const char* data, size_t size);
        const char* readData(size_t size);
		void setPointerPosition(size_t size);

        const size_t size() const { return m_data.size(); };

        template<typename T>
        typename std::enable_if<std::is_trivially_copyable<T>::value>::type
            writeObject(const T& object) {
            size_t size = sizeof(T);
            writeData((const char*)&size, sizeof(size_t));
            writeData(reinterpret_cast<const char*>(&object), sizeof(T));
        }

        template<typename T>
        typename std::enable_if<!std::is_trivially_copyable<T>::value>::type
            writeObject(const T& object) {
            // Ensure that T has a serialize method
            static_assert(has_serialize_method<T>::value,
                "T must have a serialize function with signature void (athena::buffer*, const T&)");

            // Call the serialize method on the object
            T::serialize(this, object);
        }

        template<typename T>
        void writeArray(const std::vector<T>& vector)
        {
            size_t vectorSize = vector.size();

            writeData((const char*)&vectorSize, sizeof(size_t));
            for (size_t i = 0; i < vector.size(); i++)
                writeObject(vector[i]);
        }
#pragma endregion
#pragma region serialize
        static void serialize(buffer* p_dstBuffer,const buffer& srcBuffer)
        {
            size_t srcSize = srcBuffer.size();

            p_dstBuffer->writeData((const char*)& srcSize, sizeof(size_t));
            p_dstBuffer->writeData((const char*)srcBuffer.m_data.data(), srcBuffer.size());
        }
        static buffer& deserialize(buffer* p_srcBuffer)
        {
            buffer* p_dstBuffer = new buffer();

            size_t size = *(size_t*)p_srcBuffer->readData(sizeof(size_t));

            p_dstBuffer->writeData(p_srcBuffer->readData(size), size);

            return *p_dstBuffer;
        }
#pragma endregion
#pragma region read
        template<typename T>
        typename std::enable_if<std::is_trivially_copyable<T>::value,T>::type
            readObject() {
            size_t structSize = sizeof(T);
            size_t storedStructSize = *(size_t*)readData(sizeof(size_t));
            if(structSize == storedStructSize) return *(T*)readData(structSize);

            T* p_struct = (T*)malloc(structSize);
            const char* p_src = readData(storedStructSize);

            if (structSize > storedStructSize)
            {
                memcpy_s(reinterpret_cast<char*>(p_struct), storedStructSize, p_src, storedStructSize);
                memset(reinterpret_cast<char*>(p_struct) + storedStructSize, 0, structSize - storedStructSize);
            }
            else
                memcpy_s(reinterpret_cast<char*>(p_struct), structSize, p_src, structSize);

            
            delete[] p_src;
            return *p_struct;
            
        }

        template<typename T>
        typename std::enable_if<!std::is_trivially_copyable<T>::value,T>::type
            readObject() {
            // Ensure that T has a serialize method
            static_assert(has_deserialize_method<T>::value,
                "T must have a deserialize function with signature T& (athena::buffer*)");
            // Call the serialize method on the object
           return T::deserialize(this);
        }

        template<typename T>
        std::vector<T>& readArray()
        {
            std::vector<T>* dstVector = new std::vector<T>();

            size_t storedArraySize = *(size_t*)readData(sizeof(size_t));

            for (size_t i = 0; i < storedArraySize; i++)
                dstVector->push_back(readObject<T>());

            return *dstVector;
        }
#pragma endregion
        uint8_t* data() { return m_data.data(); }
		operator size_t() const { return m_data.size(); };
	protected:
		size_t m_pointerPosition = 0; //this allows for data to be inserted in the middle of the buffer!
		std::vector<uint8_t> m_data; //we use data vector for convenience
	};

}
#endif // !BUFFER
