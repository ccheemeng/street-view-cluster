FROM python:3.12.7-bookworm
WORKDIR /app

COPY libxp6_1.0.2-2ubuntu1~18.04_i386.deb ./
COPY graph-segmentation ./graph-segmentation/
COPY ImageMagick.tar.gz ./
COPY app.zip ./
COPY v73 ./v73/
COPY requirements.txt ./

RUN dpkg --add-architecture i386 && apt-get update &&\
    apt-get install -y libc6-i386 && apt-get install -y libxext6:i386 && dpkg -i libxp6_1.0.2-2ubuntu1~18.04_i386.deb && apt-get install -y libxt6:i386 &&\
    pip install --no-cache-dir -r requirements.txt

WORKDIR /app/graph-segmentation
RUN mkdir -p input && mkdir -p output && make

WORKDIR /app
RUN tar -xzf ImageMagick.tar.gz
WORKDIR /app/ImageMagick-7.1.1-39
RUN ./configure && make && make install

WORKDIR /app
RUN unzip app.zip
WORKDIR /app/app
RUN mkdir -p input && mkdir -p output

WORKDIR /app

ENV LD_LIBRARY_PATH="/usr/local/lib:/app/v73/runtime/glnx86:/app/v73/sys/os/glnx86:/app/v73/sys/java/jre/glnx86/jre1.5.0/lib/i386/native_threads:/app/v73/sys/java/jre/glnx86/jre1.5.0/lib/i386/client:/app/v73/sys/java/jre/glnx86/jre1.5.0/lib/i386:/app/v73/bin/glnx86"
ENV XAPPLRESDIR="/app/v73/X11/app-defaults"

EXPOSE 8005

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8005", "--no-browser", "--allow-root", "--NotebookApp.token='generate-segmentation'"]