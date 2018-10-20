import speech_recognition

rec = speech_recognition.Recognizer()
with speech_recognition.AudioFile('commands.wav') as source:
	audio = rec.record(source)
print(rec.recognize_wit(audio, "MRC3OPBK2T366ILOXGCSOCXOFAVA7CXH").lower())
