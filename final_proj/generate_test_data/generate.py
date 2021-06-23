import names
from random import randrange

num_mails      = 10
length_content = 100
length_subject = 10

# generate mail content from database
database = open("database", "r")
database_string = database.readline()

# split string
str = database_string

contents = [str[i:i+length_content] for i in range(0, len(str), length_content)]
subjects = [str[i:i+length_subject] for i in range(0, len(str), length_subject)]



f = open("test_data", "w")

# number of mails
f.write('{}\n'.format(num_mails)) 

# header of test data
f.write("=== dc685a9c7684059f ===\n")

for i in range(num_mails):

  mail_index = i
  
  ## mail index 
  f.write('{}\n'.format(mail_index))
  
  # sender
  f.write(names.get_full_name()+"\n")
  
  # content
  f.write(contents[randrange(len(contents))]+"\n")
  
  # subject
  f.write(subjects[randrange(len(subjects))]+"\n")
  
  # reciever
  f.write(names.get_full_name()+"\n")
  
  # header of mail
  f.write("=== e47bbae5876702dc ===\n")

# number of mails
f.write('{}\n'.format(num_mails)) 

# header of test data
f.write("=== dc685a9c7684059f ===\n")

for i in range(num_mails):
  f.write("1 1.210495\n")
  f.write("e\n")
  f.write("((ptprj)&(amalienplatz)|(subrata)&(tke)|(acf))&(!theorize)&((6662)&(oath)|(!mitsunori))&(!gp9)|(!influenza)\n")
  f.write("=== e47bbae5876702dc ===\n")
