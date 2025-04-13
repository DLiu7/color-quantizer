# Color Quantizer 🎨⇢🖊️  
**Fast 24-bit to 8-bit image conversion using K-means clustering**  

A Python/C hybrid tool that converts 24-bit color images to optimized 8-bit indexed images using K-means clustering. Implements both Python and C versions (via CTypes) for performance comparison. Generates a colormap and supports customizable clustering parameters (seed, iterations, centroids). Useful for palette optimization and image compression.

---

## Features  
- **Hybrid Python/C K-means** – Compare native Python vs. C-accelerated clustering speeds  
- **Customizable palettes** – Control the number of colors (`--num_centroids`) and clustering iterations  
- **Lightweight output** – Generates:  
  - 8-bit indexed images (PNG)  
  - Colormap files (text)  
- **Reproducible results** – Fixed random seed (`--seed`) for deterministic output  

---

## Installation  
1. **Compile the C library**:  
   ```bash
   gcc -O3 -shared -o libkernel.so -fPIC kernel.c
2. **Install Python Dependencies**
   ```bash
   pip install numpy pillow

## Usage
python3 24Bit.py input.png output_py.png output_c.png colormap_py.txt colormap_c.txt \
    --seed 214 \
    --num_centroids 256 \
    --max_iters 10

| Argument             | Description                                | Default     |
|----------------------|--------------------------------------------|-------------|
| `input_image`        | 24-bit input image path                    | Required    |
| `output_image`       | Python output path (8-bit PNG)             | Required    |
| `output_image_C`     | C output path (8-bit PNG)                  | Required    |
| `output_colormap`    | Python colormap path (TXT)                 | Required    |
| `output_colormap_C`  | C colormap path (TXT)                      | Required    |
| `--seed`             | Random seed for centroid initialization    | `214`       |
| `--num_centroids`    | Number of colors in palette (≤256)         | `256`       |
| `--max_iters`        | Max K-means iterations                     | `10`        |
