FROM python:3.11.10-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu && pip install -r requirements.txt
RUN apt-get update && apt-get install -y python3-ipykernel

RUN wget https://huggingface.co/depth-anything/Depth-Anything-V2-Metric-VKITTI-Large/resolve/main/depth_anything_v2_metric_vkitti_vitl.pth
RUN git clone https://github.com/DepthAnything/Depth-Anything-V2
RUN cp -a ./Depth-Anything-V2/metric_depth/. ./

EXPOSE 8012

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8012", "--no-browser", "--allow-root", "--NotebookApp.token='depth-segment-images-cpu'"]