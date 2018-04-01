import whisper
import os

# Prompts to delete a file if it exists, returns true if file does not exist
# or is deleted
def prompt_delete(file):
    if os.path.isfile(file):
        delete = raw_input(file + " exists, delete and replace? ")
        if delete.strip()[0].lower() == 'y':
            os.remove(file)
            return True
        else:
            return False
    else:
        return True

if prompt_delete("DB/Latency"):
    whisper.create("DB/Latency",
        [ (1, 24*60*60) # 1 record per second for a day
        # , (60, 7*24*60) # 1 record per minute for a week
        , (24*60*60, 365) # 1 record per day for a year
        ], aggregationMethod='max')
