FROM python:3.12.7-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg &&\
    curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
        sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
        tee /etc/apt/sources.list.d/nvidia-container-toolkit.list &&\
    apt-get update &&\
    apt-get install -y python3-ipykernel &&\
    apt-get install -y nvidia-container-toolkit &&\
    pip install --no-cache-dir -r requirements.txt && pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu121

COPY modelnet40_checkpoint.t7 ./
COPY all_id.txt ./

EXPOSE 8016

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8016", "--no-browser", "--allow-root", "--NotebookApp.token='encode-point-clouds-cuda121'"]