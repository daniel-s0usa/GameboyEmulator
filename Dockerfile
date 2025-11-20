# Use the latest Ubuntu LTS image
FROM ubuntu:24.04

# Prevent interactive prompts during install
ENV DEBIAN_FRONTEND=noninteractive

# Update packages and install common tools
RUN apt-get update && apt-get install -y --no-install-recommends \
        bash \
        curl \
        wget \
        nano \
        build-essential \
        cmake \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set default working directory
WORKDIR /app

# Copy your project files (optional)
# COPY . /app

# Default command (can be changed)
CMD ["/bin/bash"]
