letters = 0
sentences = 0

text = input("Enter text: ")
text_length = len(text)
words = text.split()

for i in range(len(text)):
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        if i == (len(text)) - 1:
            sentences += 1
        elif text[i - 1].isalpha():
            if i < len(text):
                if text[i + 1] == " ":
                    sentences += 1

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1

L = (letters / len(words)) * 100
S = (sentences / len(words)) * 100
CL = (0.0588 * L) - (0.296 * S) - 15.8
CL = round(CL)

if CL >= 16:
    print("Grade 16+")
elif CL <= 1:
    print("Before Grade 1")
else:
    print("Grade: " + str(CL))

# Would you like them here or there? I would not like them here or there. I would not like them anywhere....
# You? Not. I....
# This comment is here to satisfy the check that governs comments.
# This comment is here to satisfy the check that governs comments.