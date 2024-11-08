FROM python:3.11.10-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg &&\
    curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
        sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
        tee /etc/apt/sources.list.d/nvidia-container-toolkit.list &&\
    apt-get update &&\
    apt-get install -y python3-ipykernel &&\
    apt-get install -y nvidia-container-toolkit &&\
    pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu121 && pip install --no-cache-dir -r requirements.txt &&\
    wget https://huggingface.co/depth-anything/Depth-Anything-V2-Metric-VKITTI-Large/resolve/main/depth_anything_v2_metric_vkitti_vitl.pth &&\
    git clone https://github.com/DepthAnything/Depth-Anything-V2 &&\
    cp -a ./Depth-Anything-V2/metric_depth/. ./

EXPOSE 8018

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8018", "--no-browser", "--allow-root", "--NotebookApp.token='depth-segment-images-cuda121'"]