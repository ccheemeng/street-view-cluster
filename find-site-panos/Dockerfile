FROM python:3.12.7-bookworm
WORKDIR /app

COPY requirements.txt ./
COPY geo/ ./geo/
COPY streetview/ ./streetview/
RUN pip install --no-cache-dir -r requirements.txt &&\
    apt-get update && apt-get install -y python3-ipykernel

EXPOSE 8002

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8002", "--no-browser", "--allow-root", "--NotebookApp.token='find-site-panos'"]