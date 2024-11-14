# OpenCl-Docker-ImageConversion
A high-performance tool for converting RGB images to grayscale using OpenCL for GPU or CPU acceleration, designed for fast and efficient image processing.




# OpenCL RGB to Grayscale Image Converter

This project is a high-performance RGB-to-grayscale image converter using **OpenCL** to leverage GPU or CPU parallel processing. It efficiently processes images by taking an input RGB image, converting it to grayscale, and outputting a new image file.

## Key Features
- **High-Performance**: Utilizes OpenCL for parallel processing, enabling fast image processing by harnessing the power of GPUs or multi-core CPUs.
- **Cross-Platform Compatibility**: Compatible with any platform that supports OpenCL, making it a versatile tool.
- **Lightweight**: Uses `stb_image` for loading images and `stb_image_write` for saving them, keeping the setup minimal and easy to integrate.

## How It Works
1. **Load the Image**: Reads an input RGB image using `stb_image`.
2. **OpenCL Initialization**: Sets up an OpenCL context and command queue, creating buffers for the input RGB data and the output grayscale data.
3. **Grayscale Conversion**: The `rgb_to_grayscale` kernel calculates the grayscale value for each pixel using a perceptual formula to maintain natural brightness.
4. **Save the Output**: The grayscale image is saved using `stb_image_write`.

## Dependencies
- **OpenCL**: Ensure that OpenCL is installed and configured on your machine to take advantage of GPU or CPU acceleration.
- **stb_image and stb_image_write**: These lightweight libraries are included for image loading and saving.

## Usage Instructions
1. Clone the repository and compile the program, linking the OpenCL library.
2. Place an RGB image file as `input.jpg` in the project directory.
3. Run the program, and it will output a grayscale version as `output.jpg`.

## About
Created by Hayat Sikandar , this project showcases a passion for high-performance computing and image processing, demonstrating the power of OpenCL for efficient data handling and transformation.
