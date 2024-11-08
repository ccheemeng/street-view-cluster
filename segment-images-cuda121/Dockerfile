FROM python:3.11.10-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg &&\
    curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
        sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
        tee /etc/apt/sources.list.d/nvidia-container-toolkit.list &&\
    apt-get update && apt-get install -y python3-ipykernel &&\
    apt-get install -y nvidia-container-toolkit &&\
    pip install torch==2.1.2 torchvision==0.16.2 torchaudio==2.1.2 --index-url https://download.pytorch.org/whl/cu121 &&\
    pip install mmcv==2.1.0 -f https://download.openmmlab.com/mmcv/dist/cu121/torch2.1/index.html &&\
    pip install --no-cache-dir -r requirements.txt

COPY configs ./configs/

EXPOSE 8017

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8017", "--no-browser", "--allow-root", "--NotebookApp.token='segment-images-cuda121'"]