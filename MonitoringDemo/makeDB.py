import whisper

whisper.create("Latency", [(1,1000000)], aggregationMethod='max')
