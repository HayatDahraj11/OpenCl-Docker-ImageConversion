FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install -y pocl-opencl-icd ocl-icd-opencl-dev gcc clinfo

WORKDIR /app

COPY host.c /app/
COPY stb_image.h /app/
COPY stb_image_write.h /app/
COPY input.jpg /app/
COPY input2.jpg /app/
COPY input3.jpg /app/
COPY input4.jpg /app/
COPY input5.jpg /app/
COPY input6.jpg /app/
COPY host2.jpg /app/





