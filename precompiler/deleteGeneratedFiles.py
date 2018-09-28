import os

dirsToSearch = [
    "../src",    #core
    "../plugins" #plugins
]

filesToWalk = []
for dir in dirsToSearch:
    for root, directories, files in os.walk(dir):
        files = [os.path.join(root, file) for file in files if file.endswith(".generated.cpp")]
        filesToWalk.extend(files)

for file in filesToWalk:
    print("Delete file", file)
    os.remove(file)