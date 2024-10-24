FROM python:3.12.7-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt && pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu &&\
    apt-get update && apt-get install -y python3-ipykernel

COPY modelnet40_checkpoint.t7 ./
COPY all_id.txt ./

EXPOSE 8008

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8008", "--no-browser", "--allow-root", "--NotebookApp.token='encode-point-clouds-cpu'"]