from pyproj import Transformer

# Restricted wrapper class around pyproj.Transformer
class Transform:
    def __init__(self, crs_from: int, crs_to: int):
        self.transformer = Transformer.from_crs(f"EPSG:{crs_from}", f"EPSG:{crs_to}", always_xy=True)
        self.useless = crs_from == crs_to

    def transform3d(self, xyz: tuple[float, float, float]) -> tuple[float, float, float]:
        if self.useless:
            return xyz
        xy_new = self.transform2d((xyz[0], xyz[1]))
        return (xy_new[0], xy_new[1], xyz[2])
    
    def transform2d(self, xy: tuple[float, float]) -> tuple[float, float]:
        if self.useless:
            return xy
        return self.transformer.transform(xy[0], xy[1])