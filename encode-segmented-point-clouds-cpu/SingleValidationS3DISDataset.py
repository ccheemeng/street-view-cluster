import numpy as np

from datasets.common import PointCloudDataset

import time

class SingleValidationS3DISDataset(PointCloudDataset):
    def __init__(self, config, ply_path, set="validation", use_potentials=True, load_data=True):
        PointCloudDataset.__init__(self, "S3DIS")

        self.label_to_names = {
            0: 'ceiling',
            1: 'floor',
            2: 'wall',
            3: 'beam',
            4: 'column',
            5: 'window',
            6: 'door',
            7: 'chair',
            8: 'table',
            9: 'bookcase',
            10: 'sofa',
            11: 'board',
            12: 'clutter'
        }
        self.num_classes = len(self.label_to_names)
        self.label_values = np.sort([k for k, v in self.label_to_names.items()])
        self.label_names = [self.label_to_names[k] for k in self.label_values]
        self.label_to_idx = {l: i for i, l in enumerate(self.label_values)}
        self.name_to_label = {v: k for k, v in self.label_to_names.items()}
        self.ignored_labels = np.array([])
        self.dataset_task = "cloud_segmentation"
        config.num_classes = self.num_classes - len(self.ignored_labels)
        config.dataset_task = self.dataset_task
        self.config = config
        self.set = set
        self.use_potentials = use_potentials
        self.ply_path = ply_path
        self.input_trees = []
        self.input_colors = []
        self.input_labels = []
        self.pot_trees = []
        self.num_clouds = 0
        self.test_proj = []
        self.validation_labels = []
    
    def prepare_S3DIS_ply(self):
        print("\nPreparing ply files")
        t0 = time.time()

        