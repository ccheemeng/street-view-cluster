# Street View Cluster  

This is a working collection of a series of pipelines for working with image and point cloud data derived from Google Street View.  

1. [util](/notebooks/util.ipynb): data conversions, labelling, image resizing, and other utilities.  
2. [collect-street-view](/notebooks/collect-street-view.ipynb): download panoramas and their corresponding depth maps from Google Street View.  
3. [find-site-panos](/notebooks/find-site-panos.ipynb): find all Google Street View panoramas with an available depth map within a bounding rectangle.  
4. [generate-gist](/notebooks/generate-gist.ipynb): evaluate the GIST descriptor of an image.  
5. [generate-textonmap](/notebooks/generate-textonmap.ipynb): generate the textonmap of an image.  
6. [generate-segmentation](/notebooks/generate-segmentation.ipynb): segment an image into its ground, sky, vertical, and porous components.  
7. [encode-panos](/notebooks/encode-panos.ipynb): encode panoramas as described in Naik et al (2014).  
8. [encode-images](/notebooks/encode-images.ipynb): encode panoramas with a process derived from Naik et al (2014).  
9. [encode-point-clouds](/notebooks/encode-point-clouds.ipynb): encode point clouds derived from Li et al (2021). *CUDA option to be added*  
10. [cluster-data](/notebooks/cluster-data.ipynb): a notebook interface to perform k-means clustering.  
11. [train-svr](/notebooks/train-svr.ipynb): a notebook interface to perform regression via a SVM.  
12. [segment-images](/notebooks/segment-images.ipynb): semantically segment an image with the OpenMMLab Semantic Segmentation Toolbox and Benchmark. *CUDA option to be added*  
13. [depth-segment-images](/notebooks/depth-segment-images.ipynb): estimate the metric depth of an image with Depth Anything V2. *CUDA option to be added*  

## Installation  

### Individual Notebooks  

To use the pipeline described by one notebook, build and run its respective Docker image. For example, to use the pipelines in [util.ipynb](/notebooks/util.ipynb):  
```shell  
sh ./util/build-util.sh  
sh ./util/run-util.sh  
```  

To build all Docker images, use Docker Compose:  
```shell  
docker-compose build  
docker-compose up -d  
```  

## Usage  

Follow the instructions in the respective notebook to use it. In general and if Dockerfiles have not been modified, you may connect to the respective Jupyter server with ```http://localhost:<port>/tree?token=<pipeline name>```.  

For example, you may connect to the Jupyter server for [util.ipynb](/notebooks/util.ipynb) with ```http://localhost:8000/tree?token=util```.  

Port numbers are described in [docker-compose.yml](docker-compose.yml) and stated in the respective notebooks.  

## Acknowledgement  

### Datasets

* [Place Pulse 2.0 dataset](https://www.dropbox.com/s/grzoiwsaeqrmc1l/place-pulse-2.0.zip?dl=0)  

### Code and Software

* [Depth-Anything-V2](https://github.com/DepthAnything/Depth-Anything-V2)  
* [graph-segmentation](https://github.com/fsrajer/graph-segmentation)  
* [lear-gist-python](https://github.com/whitphx/lear-gist-python)  
* [mmsegmentation](https://github.com/open-mmlab/mmsegmentation)  
* [PbLite-Contour-Detection](https://github.com/rohithjayarajan/PbLite-Contour-Detection)  
* [Photo Pop-up](https://dhoiem.cs.illinois.edu/projects/software.html)  
* [rotation-invariant-pointcloud-analysis](https://github.com/feiran-l/rotation-invariant-pointcloud-analysis)  
* [streetlevel](https://github.com/sk-zk/streetlevel)  

### Papers

> Dubey, A., Naik, N., Parikh, D., Raskar, R., Hidalgo, C.A. (2016). Deep Learning the City: Quantifying Urban Perception at a Global Scale. In: Leibe, B., Matas, J., Sebe, N., Welling, M. (eds) Computer Vision – ECCV 2016. ECCV 2016. Lecture Notes in Computer Science(), vol 9905. Springer, Cham. https://doi.org/10.1007/978-3-319-46448-0_12  

> D. Hoiem, A. A. Efros and M. Hebert, "Geometric context from a single image," Tenth IEEE International Conference on Computer Vision (ICCV'05) Volume 1, Beijing, China, 2005, pp. 654-661 Vol. 1, doi: 10.1109/ICCV.2005.107  

> Felzenszwalb, P.F., Huttenlocher, D.P. Efficient Graph-Based Image Segmentation. International Journal of Computer Vision 59, 167–181 (2004). https://doi.org/10.1023/B:VISI.0000022288.19776.77  

> F. Li, K. Fujiwara, F. Okura and Y. Matsushita, "A Closer Look at Rotation-invariant Deep Point Cloud Analysis," 2021 IEEE/CVF International Conference on Computer Vision (ICCV), Montreal, QC, Canada, 2021, pp. 16198-16207, doi: 10.1109/ICCV48922.2021.01591.  

> N. Naik, J. Philipoom, R. Raskar and C. Hidalgo, "Streetscore -- Predicting the Perceived Safety of One Million Streetscapes," 2014 IEEE Conference on Computer Vision and Pattern Recognition Workshops, Columbus, OH, USA, 2014, pp. 793-799, doi: 10.1109/CVPRW.2014.121.  

> Oliva, A., Torralba, A. Modeling the Shape of the Scene: A Holistic Representation of the Spatial Envelope. International Journal of Computer Vision 42, 145–175 (2001). https://doi.org/10.1023/A:1011139631724  

> Salesses P, Schechtner K, Hidalgo CA (2013) The Collaborative Image of The City: Mapping the Inequality of Urban Perception. PLOS ONE 8(7): e68400. https://doi.org/10.1371/journal.pone.0068400  

> Yang, L., Kang, B., Huang, Z., Zhao, Z., Xu, X., Feng, J., & Zhao, H. (2024). Depth Anything V2 (arXiv:2406.09414). arXiv. https://doi.org/10.48550/arXiv.2406.09414  
