FROM python:3.12.7-bookworm
WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
RUN apt-get update && apt-get install -y python3-ipykernel

EXPOSE 8000:8000

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8000", "--no-browser", "--allow-root", "--NotebookApp.token='util'"]