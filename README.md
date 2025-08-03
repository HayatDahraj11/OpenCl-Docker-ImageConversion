# OpenCL RGB to Grayscale Image Converter

A high-performance image processing application that converts RGB images to grayscale using OpenCL for GPU acceleration. This implementation leverages parallel computing to efficiently process images using the standard luminance formula.

## Features

- **GPU-Accelerated Processing**: Uses OpenCL to parallelize grayscale conversion across GPU cores
- **Standard Luminance Formula**: Implements the ITU-R BT.709 standard (0.2126×R + 0.7152×G + 0.0722×B)
- **Multiple Image Format Support**: Handles JPEG, PNG, BMP, and other formats via STB libraries
- **Memory Efficient**: Direct GPU memory operations minimize CPU-GPU data transfers
- **Cross-Platform**: Compatible with any OpenCL-supported device (NVIDIA, AMD, Intel GPUs)

## Prerequisites

### System Requirements
- OpenCL-compatible GPU or CPU
- OpenCL drivers installed
- C compiler (GCC, Clang, or MSVC)

### Dependencies
- **OpenCL**: Development headers and libraries
- **STB Libraries**: Already included in the project
  - `stb_image.h` - Image loading
  - `stb_image_write.h` - Image saving

### Installation of Dependencies

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install ocl-icd-opencl-dev opencl-headers
# For NVIDIA GPUs
sudo apt-get install nvidia-opencl-dev
# For AMD GPUs  
sudo apt-get install amd-opencl-dev
```

#### Linux (RHEL/CentOS/Fedora)
```bash
sudo yum install opencl-headers ocl-icd-devel
# or for newer versions
sudo dnf install opencl-headers ocl-icd-devel
```

#### macOS
```bash
# OpenCL is included with macOS
brew install gcc  # if using Homebrew for GCC
```

#### Windows
- Install GPU vendor-specific SDK (CUDA for NVIDIA, ROCm for AMD)
- Or use Intel OpenCL SDK for Intel GPUs

## Building

### Linux/macOS
```bash
gcc -o grayscale_converter paste.c -lOpenCL -lm
```

### Windows (Visual Studio)
```cmd
cl paste.c /link OpenCL.lib
```

### Alternative with Makefile
Create a `Makefile`:
```makefile
CC=gcc
CFLAGS=-Wall -O2
LIBS=-lOpenCL -lm

grayscale_converter: paste.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f grayscale_converter
```

Then build with:
```bash
make
```

## Usage

1. **Prepare your input image**: Place your input image in the same directory as the executable and name it `input2.jpg`

2. **Run the converter**:
   ```bash
   ./grayscale_converter
   ```

3. **Output**: The grayscale image will be saved as `output2.jpg`

### Modifying Input/Output Files
To use different file names, modify these lines in the source code:
```c
// Change input file
unsigned char *img = stbi_load("your_input.jpg", &width, &height, &channels, 3);

// Change output file  
stbi_write_jpg("your_output.jpg", width, height, 1, gray, 100);
```

## How It Works

### Technical Overview

1. **Image Loading**: Uses STB library to load RGB image data into memory
2. **OpenCL Setup**: Initializes OpenCL platform, device, context, and command queue
3. **Kernel Compilation**: Compiles the grayscale conversion kernel at runtime
4. **Memory Management**: Creates OpenCL buffers for input RGB and output grayscale data
5. **Parallel Execution**: Launches kernel with 2D work groups (width × height)
6. **Result Retrieval**: Reads processed grayscale data back from GPU memory
7. **Image Saving**: Saves the result as JPEG using STB library

### Grayscale Conversion Formula
The program uses the standard luminance formula recommended by ITU-R BT.709:
```
Grayscale = 0.2126 × Red + 0.7152 × Green + 0.0722 × Blue
```

This formula accounts for human eye sensitivity to different colors.

### OpenCL Kernel
The GPU kernel processes each pixel independently:
```c
__kernel void rgb_to_grayscale(__global const unsigned char *img, 
                               __global unsigned char *gray, 
                               const int width, const int height)
```

## Performance Benefits

- **Parallel Processing**: Each pixel is processed simultaneously on different GPU cores
- **Memory Bandwidth**: GPU's high memory bandwidth accelerates data access
- **Scalability**: Performance scales with image size and GPU capability

## File Structure

```
project/
├── paste.c              # Main source code
├── stb_image.h          # STB image loading library (header-only)
├── stb_image_write.h    # STB image writing library (header-only)
├── input2.jpg           # Your input image
├── output2.jpg          # Generated grayscale output
└── README.md            # This file
```

## Troubleshooting

### Common Issues

**"Unable to get platform ID"**
- Ensure OpenCL drivers are installed
- Check if your GPU supports OpenCL

**"Failed to load image"**
- Verify `input2.jpg` exists in the working directory
- Check if the image format is supported
- Ensure the image file is not corrupted

**Compilation errors**
- Verify OpenCL headers are installed
- Check linker flags (`-lOpenCL`)
- Ensure STB header files are in the include path

**Runtime crashes**
- Check available GPU memory for large images
- Verify OpenCL drivers are up to date

### Debugging
Add error checking by examining OpenCL error codes:
```c
printf("OpenCL Error Code: %d\n", err);
```

## Supported Image Formats

**Input**: JPEG, PNG, TGA, BMP, PSD, GIF, HDR, PIC, PNM  
**Output**: JPEG (quality 100)

## License

This project uses:
- STB libraries (Public Domain)
- OpenCL (Khronos Group specification)

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## Future Enhancements

- Command-line argument support for input/output files
- Multiple output format options
- Batch processing capability
- Advanced image filters (blur, sharpen, etc.)
- Performance benchmarking tools
