FROM python:3.11.10-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip install torch==2.1.2 torchvision==0.16.2 torchaudio==2.1.2 --index-url https://download.pytorch.org/whl/cpu &&\
    pip install mmcv==2.1.0 -f https://download.openmmlab.com/mmcv/dist/cpu/torch2.1/index.html &&\
    pip install --no-cache-dir -r requirements.txt &&\
    apt-get update && apt-get install -y python3-ipykernel

COPY configs ./configs/

EXPOSE 8011

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8011", "--no-browser", "--allow-root", "--NotebookApp.token='segment-images-cpu'"]