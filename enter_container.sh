docker build -t buildimage .

docker run -it  -v $(pwd):/app buildimage
