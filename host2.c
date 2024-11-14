#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

const char *kernelSource =
    "__kernel void rgb_to_grayscale(__global const unsigned char *img, __global unsigned char *gray, const int width, const int height) {"
    "    int x = get_global_id(0);"
    "    int y = get_global_id(1);"
    "    if (x < width && y < height) {"
    "        int i = y * width + x;"
    "        int r = img[3*i];"
    "        int g = img[3*i + 1];"
    "        int b = img[3*i + 2];"
    "        gray[i] = (unsigned char)(0.2126f * r + 0.7152f * g + 0.0722f * b);"
    "    }"
    "}";

int main() {
    int width, height, channels;
    unsigned char *img = stbi_load("input2.jpg", &width, &height, &channels, 3);
    if (!img) {
        fprintf(stderr, "Failed to load image.\n");
        return -1;
    }

    size_t img_size = width * height * 3;  // 3 channels (RGB)
    size_t gray_size = width * height;

    cl_int err;
    cl_platform_id platform_id;
    cl_device_id device_id;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;

    // Initialize OpenCL environment
    err = clGetPlatformIDs(1, &platform_id, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Unable to get platform ID\n");
        return -1;
    }

    err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Unable to get device ID\n");
        return -1;
    }

    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Unable to create context\n");
        return -1;
    }

    queue = clCreateCommandQueue(context, device_id, 0, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Unable to create command queue\n");
        return -1;
    }

    program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Unable to create program\n");
        return -1;
    }

    err = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Error building program\n");
        return -1;
    }

    kernel = clCreateKernel(program, "rgb_to_grayscale", &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Unable to create kernel\n");
        return -1;
    }

    // Create memory buffers
    cl_mem img_mem = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, img_size, img, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Failed to create buffer for input image\n");
        return -1;
    }

    cl_mem gray_mem = clCreateBuffer(context, CL_MEM_WRITE_ONLY, gray_size, NULL, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Failed to create buffer for grayscale image\n");
        return -1;
    }

    // Set kernel arguments
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &img_mem);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &gray_mem);
    err |= clSetKernelArg(kernel, 2, sizeof(int), &width);
    err |= clSetKernelArg(kernel, 3, sizeof(int), &height);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Failed to set kernel arguments\n");
        return -1;
    }

    // Define an NDRange
    size_t global_size[] = { (size_t)width, (size_t)height };

    // Execute the kernel
    err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Failed to enqueue NDRange kernel\n");
        return -1;
    }

    // Read back the result
    unsigned char *gray = (unsigned char *)malloc(gray_size);
    if (!gray) {
        fprintf(stderr, "Failed to allocate memory for grayscale image\n");
        return -1;
    }
    err = clEnqueueReadBuffer(queue, gray_mem, CL_TRUE, 0, gray_size, gray, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Failed to read buffer\n");
        return -1;
    }

    // Save the grayscale image
    stbi_write_jpg("output2.jpg", width, height, 1, gray, 100);

    // Cleanup
    stbi_image_free(img);
    free(gray);
    if (img_mem) clReleaseMemObject(img_mem);
    if (gray_mem) clReleaseMemObject(gray_mem);
    if (kernel) clReleaseKernel(kernel);
    if (program) clReleaseProgram(program);
    if (queue) clReleaseCommandQueue(queue);
    if (context) clReleaseContext(context);

    return 0;
}
