import os
from typing import NoReturn
import rsrfile
from zipfile import ZipFile
from tabulate import tabulate


def read_zip(file_path: str, temp_dir_name='temp') -> str:
    """ Extract a single rsr file from zip archive to temp dir """
    with ZipFile(file_path, 'r') as zipObject:
        listOfFileNames = zipObject.namelist()[1:]
        for fileName in listOfFileNames:
            if fileName.endswith('.RSR'):
                zipObject.extract(fileName, temp_dir_name)
                yield f'{temp_dir_name}/{fileName}'
                os.remove(f'{temp_dir_name}/{fileName}')
        os.rmdir(temp_dir_name)


def read_rsr_time(file_path: str) -> tuple[str, float]:
    for i, path in enumerate(read_zip(file_path)):
        f = rsrfile.open(path)
        acase_id = f.misc_summary.cDummy[1]
        yield (acase_id, f.mcs_summary.RunTimeTot)
        f.close()
        del(f)


def main() -> NoReturn:
    # display table
    head = ["ID", "Time, s"]
    print(tabulate(read_rsr_time('./examples/test.zip'),
          headers=head, tablefmt="grid"))


if __name__ == '__main__':
    main()
