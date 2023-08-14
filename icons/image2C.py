import sys
import subprocess
import os.path
from PIL import Image
from dirsync import sync

folder_svg = "dep"
folder_png = "png"
folder_header = "out"

list_sizes = [12,16,24,32,40,48,64,80,96,112,128,144,160,196,256]
files_svg = []
files_png = []
files_header = []

counter = 0
total = 0
skipped = 0
error = False

def print_header():
    global list_sizes
    print("  Image to C Header converter")
    print('  Usage: python3 image2C.py list_sizes')
    print('  Example: python3 image2C.py 16,32,64')
    print(f"\n  Arguments: {str(sys.argv)}")
    if len(sys.argv) < 2:
        print('  No list_sizes is given use default: [12,16,24,32,40,48,64,80,96,112,128,144,160,196,256]')        

    if len(sys.argv) >= 2:
        list_sizes.clear()
        for size in sys.argv[1].split(','):
            list_sizes.append(size)

    if len(list_sizes) == 0:
        print('No Sizes given')
        sys.exit(1)

def start_analysis():
    global converted_files,files_svg,files_png,files_header

    t = list_sizes[0:len(list_sizes)]
    print(f"   list_sizes: {t}")

    converted_files = [os.path.basename(f) for f in os.listdir(folder_png) if f.endswith('.png')]

    # SVG files
    for root, dirs, files in os.walk(folder_svg):
        for file in files:
            if file.endswith('.svg'):
                files_svg.append(os.path.join(root, file))
    print(f"   SVG count: {len(files_svg)}")

    if len(files_svg) == 0:
        print('No SVG files found')
        sys.exit(1)

    # PNG files
    for root, dirs, files in os.walk(folder_png):
        for file in files:
            if file.endswith('.png'):
                files_png.append(os.path.join(root, file))
    print(f"   PNG count: {len(files_png)}")

    # Header files
    for root, dirs, files in os.walk(folder_header):
        for file in files:
            if file.endswith('.h'):
                files_header.append(os.path.join(root, file))
    print(f"   HEADER count: {len(files_header)}")


def start_conversion_to_png():
    global counter, total, skipped
    counter = 0
    skipped = 0
    total = len(files_svg)

    for file in files_svg:
        counter += 1
        update_counter(file)
        convert_svg_to_png(file)
        if(error):
            print("     Conversion failed.")
            sys.exit(1)
    print(f"    Skipped: {skipped}")
    print("     Conversion completed.")

def start_conversion_to_header():
    global counter, total, skipped
    counter = 0
    skipped = 0
    total = len(files_png)

    for file in files_png:
        counter += 1
        update_counter(file)
        convert_png_to_header(file)
        if(error):
            print("     Conversion failed.")
            sys.exit(1)
    print(f"    Skipped: {skipped}")
    print("     Conversion completed.")

def update_counter(filename):
    progress = counter / total
    bar_length = 20
    filled_length = int(bar_length * progress)
    bar = '=' * filled_length + '-' * (bar_length - filled_length)

    # Move cursor to the left and clear the line
    LINE_UP = '\033[1A'
    LINE_CLEAR = '\x1b[2K'
    sys.stdout.write(LINE_UP)
    sys.stdout.write(LINE_CLEAR)

    # Print the progress bar and status
    sys.stdout.write(f'   [{bar}] {int(progress * 100)}% ({counter}/{total}) : {filename}\n')

    # Flush the output buffer
    sys.stdout.flush()

    # Überprüfe, ob der Fortschritt abgeschlossen ist
    if counter == total:
        sys.stdout.write('\n')
        sys.stdout.flush()

def convert_svg_to_png(svg_file):
    global skipped

    filename = os.path.basename(svg_file).replace(".svg","",1)
    processes = []
    
    for size in list_sizes:
        new_folder = os.path.dirname(svg_file)
        new_folder = new_folder.replace(folder_svg, folder_png, 1)
        new_folder = os.path.join(new_folder, str(size))
        
        os.makedirs(new_folder, exist_ok=True)

        png_file = os.path.join(new_folder, f"{filename}_{size}x{size}.png")

        if(os.path.exists(png_file)):
           skipped += 1
           continue

        command = ["inkscape", "-z", "--export-background=\"#ffffff\"", "-e", png_file, "-w", str(size), "-h", str(size), svg_file]
        process = subprocess.Popen(command)
        processes.append(process)
        
    for process in processes:
        process.wait()

def convert_png_to_header(png_file):
    global skipped

    folder = os.path.dirname(png_file)
    filename = os.path.basename(png_file).replace(".png",".h",1)

    # Create new folder if it doesn't exist
    new_folder = folder.replace(folder_png,folder_header,1)
    os.makedirs(new_folder, exist_ok=True)

    # Create new header filename
    h_file = os.path.join(new_folder, filename.replace(".png",".h").replace("-","_"))
    if(os.path.exists(h_file)):
        skipped += 1
        return
    
    # Convert PNG file to header file
    convert_png_to_header_file(png_file, h_file)


def convert_png_to_header_file(input_file,output_file):
    global error
    BITES_PER_LINE = 16
    BITS_PER_BYTE = 8
    THRESHOLD = 127
    byte_array = bytearray()
    
    try:
        with Image.open(input_file) as image_file:
            src_g = image_file.convert('L')
            pixels = list(src_g.getdata())
            width, height = image_file.size  
            
            data = bytearray()    
            # Iterate Over Height
            for y in range(0,len(pixels),width):

                # Iterate over width
                for x in range (y, y + width, 8):
                    
                    byte = 0    
                    # Create new byte 
                    for i in range(8):
                        index = x + i
                        
                        if index >= len(pixels):
                            break

                        if index >= y + width:
                            continue
                        
                        if pixels[index] > THRESHOLD:
                            byte |= (1<<(7 - i)) 
                    data.append(byte)
                
    except Exception as e:
        print("Error:", e)
        error = True
        sys.exit(1)  
            
    try:
        with open(output_file, "w") as f:                
            f.write(f"// Automatically generated by image2C.py (Do not modify it)\n")
            f.write("// {} : {} x {}\n\n".format(output_file, width, height))
            file_name = os.path.basename(output_file).rsplit('.h', 1)[0]    
            f.write(f"const unsigned char IMG_{file_name}[] PROGMEM = {{\n  ")
            
            for i in range(len(data)):
                f.write(f"0x{data[i]:02x}")
                if i != len(data) - 1:
                    f.write(", ")      
                if (i+1) % 12 == 0:
                    f.write("\n  ")
            f.write("\n};")
            f.close()

    except Exception as e:
        print("Error:", e)
        error = True
        sys.exit(1)

def generate_includes():
    icons_file_path = os.path.join(folder_header, 'icons.h')
    
    try:
        with open(icons_file_path, 'w') as f:
            f.write("#pragma once\n")
            f.write(f"// Automatically generated by image2C.py (Do not modify) \n\n")
            for root, _, files in os.walk(folder_header):
                for file in files:
                    if file == "icons.h":
                        continue
                    if file.endswith('.h'):
                        header_file = os.path.join(root, file)
                        header_file = header_file.replace(folder_header + "\\", "")
                        include_statement = f"#include \"{header_file}\"\n"
                        f.write(include_statement)  
            f.close()
            print(f"C++-Headerdatei {f} wurde erfolgreich erstellt.")
    except Exception as e:
        print("Error:", e)
        error = True
        sys.exit(1)
        
def sync_folder():
    source_path = folder_header
    target_path = "..\\platformio\\icons"
    sync(source_path, target_path, 'sync') #for syncing one way


def main():
    # Programm
    print("\n1) ----> image2C <---")
    print_header()

    print("\n2) Analysis...")
    start_analysis()

    print("\n3) Start Conversion to PNG...")
    try:
        start_conversion_to_png()
    except Exception as e:
        print(f"Ein Fehler ist aufgetreten: {e}")
        sys.exit(1)

    print("\n4) Start Conversion to Header ...")
    try:
        start_conversion_to_header()
    except Exception as e:
        print(f"Ein Fehler ist aufgetreten: {e}")
        sys.exit(1)

    print("\n5) Generate Include Headder ...")
    try:
        generate_includes()
    except Exception as e:
        print(f"Ein Fehler ist aufgetreten: {e}")
        sys.exit(1)

    print("6) Synchronize folder into build folder")
    sync_folder()

    print("\n6) Finished")

if __name__ == "__main__":
    main()