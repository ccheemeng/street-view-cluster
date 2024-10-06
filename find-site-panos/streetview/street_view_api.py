import asyncio
from streetlevel import streetview

class StreetViewAPI:
    @staticmethod
    async def find_pano_full(session, lat, lon, radius=50):
        base_pano = await StreetViewAPI.find_pano_id(session, lat, lon, radius=radius)
        if base_pano:
            return await StreetViewAPI.find_pano_elevation(session, base_pano.id)
        else:
            return None
    
    @staticmethod
    async def find_pano_elevation(session, panoid):
        try:
            return await streetview.find_panorama_by_id_async(panoid, session, download_depth=True)
        except Exception as e:
            print(f"{panoid}: {e}")
            return None
        
    @staticmethod
    async def find_pano_id(session, lat, lon, radius=50):
        try:
            return await streetview.find_panorama_async(lat, lon, session, radius=radius)
        except Exception as e:
            print(f"({lat}, {lon}): {e}")
            return None