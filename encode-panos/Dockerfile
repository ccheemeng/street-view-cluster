FROM python:3.12.7-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt &&\
    apt-get update && apt-get install -y python3-ipykernel

EXPOSE 8006

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8006", "--no-browser", "--allow-root", "--NotebookApp.token='encode-panos'"]