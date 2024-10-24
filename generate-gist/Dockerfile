FROM python:3.12.7-bookworm
WORKDIR /app

ENV LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib"

COPY requirements.txt ./
COPY fftw-3.3.10.tar.gz ./
COPY lear-gist-python/ ./lear-gist-python/

RUN pip install --no-cache-dir -r requirements.txt &&\
    apt-get update && apt-get install -y python3-ipykernel &&\

    tar -xzf fftw-3.3.10.tar.gz
WORKDIR /app/fftw-3.3.10
RUN ./configure --enable-single --enable-shared && make && make install
WORKDIR /app/lear-gist-python
RUN ./download-lear.sh && python setup.py build_ext && python setup.py install

WORKDIR /app

EXPOSE 8003

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8003", "--no-browser", "--allow-root", "--NotebookApp.token='generate-gist'"]