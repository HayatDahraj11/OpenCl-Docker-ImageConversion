# OpenCL-and-Docker

Docker comes in place when you have to go through the pain of installation and management of dependencies.
OpenCL (Open Computing Language) is a framework which allows you to write programs for hetrogeneous platforms.

I prepared this <a href = "https://github.com/Umar-Waseem/OpenCL-and-Docker/blob/main/dockerfile" > Dockerfile </a> to help create an environment with a Ubuntu environment that has OpenCL set up.

The docker file installs the following in an isolated Ubuntu Linux container:
- `pocl-opencl-icd`: CPU-based OpenCL implementation ( used for developing and running OpenCL applications on systems that don't have a dedicated GPU ).

- `ocl-icd-opencl-dev`: OpenCL development headers and libraries

- `gcc`: C compiler

- `clinfo`: This is a command-line utility that displays information about the available OpenCL platforms and devices 

## Get Started:

1. Download <a href = "https://www.docker.com/products/docker-desktop/" > Docker Desktop </a>. (verify succesfull installation by running `docker version` command on command line).
2. Clone this repo using `git clone https://github.com/HayatDahraj11/OpenCL-and-Docker` OR just download the zipped code.
3. Open the downloaded / cloned repo in a command line or better, open in vs code.
4. Run `docker build -t opencl-image .` (can take 3 - 8 minutes)
5. After its done, run `docker run -it opencl-image`
6. You start with `/app` directory. Verify that there is a `host.c` file in the directory.
7. Run `gcc host.c -o host -lOpenCL` to compile the code.
8. `./host` to run.

