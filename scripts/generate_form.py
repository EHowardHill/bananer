import os

final = ""

base = "/mnt/c/users/ethan/Documents/GitHub/nova-baby/"
file_list = [
    "premise.txt",
    "build_win64.sh"
]

directories = ["include", "source", "scripts"]

for dir in directories:
    for file in os.listdir(dir):
        file_list.append(dir + "/" + file)

for file in file_list:

    path = base + file

    try:
        with open(path, "r", encoding="utf-8", errors="replace") as f:
            content = f.read()
            final += f"{file}:\n{content}\n\n"
    except Exception as e:
        print(f"Skipping {path} (likely not a text file or permission error).")

with open("source.txt", "w", encoding="utf-8") as f:
    f.write(final.strip())
