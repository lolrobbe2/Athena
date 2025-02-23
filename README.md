# Athena

**Athena** is a versatile C++ library designed for efficient binary file operations, allowing developers to directly write structs, classes, raw data, and arrays into  a binary format. It combines high-performance compression with modular data management, making it an excellent tool/library for handling complex binary data storage needs.

### Key Features:

1. **LZ4 Compression**  
   Athena leverages the [LZ4](https://github.com/lz4/lz4) compression algorithm, which is known for its speed and efficiency. This feature ensures that data can be compressed and decompressed rapidly, optimizing both storage space and access times.

2. **Modular Sections with Parallel Compression**  
   Files created with Athena are divided into independent sections, each of which is compressed separately. To enhance performance, Athena compresses each section in a different thread, allowing for faster processing, especially when working with large files. This modular and parallel approach enables selective decompression of individual sections, providing flexibility when accessing or modifying specific parts of a file without needing to handle the entire file.

3. **Raw Data and Array Handling**  
   In addition to structs and classes, Athena supports direct writing of raw data and arrays. This feature makes it easier to handle a wide range of binary data types, offering flexibility in how data is structured and stored.

4. **Backward and Forward Compatibility**  
   Athena ensures that [Trivially Copyable Structs and Classes](#trivially-copyable-structs-and-classes)
 maintain compatibility across different versions, as long as changes (such as adding or removing fields) are performed in a stack-like order. This compatibility is crucial for maintaining data integrity and accessibility over time as the data structures evolve.

Athena is ideal for developers who need a high-performance, flexible solution for managing binary data in C++, with robust support for various data types, parallel compression for improved performance, and backward compatibility.

5. **No Need for external LZ4 dependancies**
   Athena contains the neccesary code to compress/decompress using LZ4 on the fly without any external library's or programs!
   in other words install and go!
## 1) build
```
to build run BUILD.bat or BUILD.sh.
this just runs the python build.py script for convenience.
```
[more info](build.md)
## 2) example:
# Athena File Stream Examples

Below are examples demonstrating how to use the `athena::fileStreamWriter` and `athena::fileStreamReader` classes to write and read binary data. The examples use a simple example struct for clarity.

## Writing Data with `athena::fileStreamWriter`

Use the `fileStreamWriter` class to write data to a binary file. This example shows how to write arrays of a custom struct to a file, including handling multiple sections:

```cpp
#include <athena.h>
#include <iostream>
#include <vector>
#include <filesystem>

struct ExampleStruct
{
    int id;
    float value;
    char name[20];
};

int main()
{
    // Specify the file path
    std::filesystem::path path = "./example.bin";

    // Create a fileStreamWriter instance
    athena::fileStreamWriter* streamWriter = new athena::fileStreamWriter(path);

    // Prepare data to write
    std::vector<ExampleStruct> data1(100);
    std::vector<ExampleStruct> data2(100);

    // Fill the vectors with example data
    for (int i = 0; i < 100; ++i)
    {
        data1[i] = { i, static_cast<float>(i) * 1.5f, "Data1" };
        data2[i] = { i + 100, static_cast<float>(i) * 2.0f, "Data2" };
    }

    // Write data to file
    streamWriter->writeArray(data1);        // Write the first array
    streamWriter->nextStreamSection();      // Move to the next section
    streamWriter->writeArray(data2);        // Write the second array
    streamWriter->flush();                  // Flush all data to the file

    // Clean up
    delete streamWriter;

    return 0;
}

```

## Reading Data with `athena::fileStreamReader`

Use the `fileStreamReader` class to read data from a binary file. Below is an example demonstrating how to read arrays of a custom struct from a file and handle multiple sections:

```cpp
#include <athena.h>
#include <iostream>
#include <vector>
#include <filesystem>


struct ExampleStruct
{
    int id;
    float value;
    char name[20];
};

int main()
{
    std::filesystem::path path = "./example.bin";

    // Create a fileStreamReader instance
    athena::fileStreamReader* streamReader = new athena::fileStreamReader(path);

    // Read data from the first section
    std::vector<ExampleStruct> data1 = streamReader->readArray<ExampleStruct>();

    // Move to the next section
    streamReader->nextStreamSection();

    // Read data from the second section
    std::vector<ExampleStruct> data2 = streamReader->readArray<ExampleStruct>();

    // Print some data to verify
    std::cout << "Data1[0]: id=" << data1[0].id << ", value=" << data1[0].value << ", name=" << data1[0].name << std::endl;
    std::cout << "Data2[0]: id=" << data2[0].id << ", value=" << data2[0].value << ", name=" << data2[0].name << std::endl;

    // Clean up
    delete streamReader;

    return 0;
}
```

## Trivially Copyable Structs and Classes

**Trivially copyable** structs or classes are those that can be copied with simple memory operations without needing special handling for copying. Here are the key characteristics:

- **Simple Memory Layout:** The struct or class contains only data members that are themselves trivially copyable. This includes fundamental types (e.g., `int`, `float`, `char`) and other trivially copyable structs.

- **No User-Defined Copy Behavior:** It does not define custom copy constructors, assignment operators, or destructors. The default implementations provided by the compiler are used.

- **No Virtual Functions or Base Classes:** The struct or class does not contain virtual functions or inherit from other classes that might complicate copying.

Trivially copyable types can be safely copied using standard memory functions like `memcpy`, which is essential for efficient data manipulation, serialization, and ensuring compatibility in binary file operations or inter-process communication. This characteristic is important for maintaining data integrity and performance in low-level data handling.
