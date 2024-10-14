FROM python:3.12.7-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip install mmcv==2.2.0 -f https://download.openmmlab.com/mmcv/dist/cpu/torch2.4/index.html && pip install -r requirements.txt
RUN apt-get update && apt-get install -y python3-ipykernel

EXPOSE 8007

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8011", "--no-browser", "--allow-root", "--NotebookApp.token='encode-images'"]