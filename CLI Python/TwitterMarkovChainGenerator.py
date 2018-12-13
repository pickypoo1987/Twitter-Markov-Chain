#!/usr/bin/env python
# encoding: utf-8
#########################################################
import tweepy # https://github.com/tweepy/tweepy # twitter-python api for getting tweets
import re # reg-ex for cleaning
import os.path # for checking whether an entered path is valid
#########################################################
#########################################################
#########################################################

#########################################################
#########################################################
#########################################################

def tokenize_text(str1):
	copy = str1
	punc = ",.;-"
	# fixes i -> I
	fixed_i = re.sub(r'(\si\s)', r' I ', copy) # fixes I

	fixed_punc1 = re.sub(r'([$.,!?-])', r' \1', fixed_i) # gives punc at end of words one space
	fixed_punc2 = re.sub(r'([$.,!?-])', r'\1 ', fixed_punc1) # gives punc at start of words one space

	# handles links
	fixed_links = fix_links(fixed_punc2) # works!

	# handles titles
	fixed_titles = fix_titles(fixed_links) # works!

	# handles contractions
	fixed_contractions = fix_contractions(fixed_titles)

	# handles acroynyms
	fixed_acronyms = fix_acroynyms(fixed_contractions)

	# handles spaces
	fixed_spaces = re.sub(r'(\s{2,})', ' ', fixed_acronyms) # works!

	fixed_periods = fix_multi_periods(fixed_spaces)

	return fixed_periods

#########################################################
#########################################################
#########################################################

def fix_links(str1):
	copy = str1

	# handles links
	copy = re.sub(r'https://t\s\.\s',"https://t.", copy) # fixes https://t. links
	copy = re.sub(r'\w\s\.\scom', '.com', copy) # fixes .com links

	return copy

#########################################################
#########################################################
#########################################################

def fix_contractions(str1):
	copy = str1

	# handles contractions
	copy = re.sub(r'ldnt', 'ldn\'t', copy) # ldnt
	copy = re.sub(r'cant', 'can\'t', copy) # cant
	copy = re.sub(r'dont', 'don\'t', copy) # dont
	copy = re.sub(r'wont', 'won\'t', copy) # wont
	copy = re.sub(r'eyre', 'ey\'re', copy) # theyre

	return copy

#########################################################
#########################################################
#########################################################

def fix_titles(str1):
	# titles = ["dr", "mr", "mrs", 'ms']
	copy = str1

	# handles titles
	copy = re.sub(r'(dr\s\.)', r'dr.', copy) # fixes dr.
	copy = re.sub(r'(mr\s\.)', r'mr.', copy) # fixes mr.
	copy = re.sub(r'(mrs\s\.)', r'mrs.', copy) # fixes mrs.
	copy = re.sub(r'(ms\s\.)', r'ms.', copy) # fixes ms.

	return copy

#########################################################
#########################################################
#########################################################

def fix_multi_periods(str1):
	copy = str1

	# DOES NOT WORK CURRENTLY...
	copy = re.sub(r'(\.\s\.\s\.\s\.\s\.\s\.)', r'....', copy) # fixes . . . . . . -> ......
	copy = re.sub(r'(\.\s\.\s\.\s\.\s\.)', r'....', copy) # fixes . . . . . -> .....
	copy = re.sub(r'(\.\s\.\s\.\s\.)', r'....', copy) # fixes . . . . -> ....
	copy = re.sub(r'(\.\s\.\s\.)', r'...', copy) # fixes . . . -> ...
	copy = re.sub(r'(\.\s\.)', r'..', copy) # fixes . . -> ..

	return copy

#########################################################
#########################################################
#########################################################

def fix_acroynyms(str1):
	# acronyms = ['u . k .', 'u . s .', 'u . s . a .',]
	copy = str1

	# handles acronyms
	copy = re.sub(r'u\s\.\ss\s\.\sa\s\.', r'U.S.A.', copy) # fixes u.s.a.
	copy = re.sub(r'u\s\.\ss\s\.', r'U.S.', copy) # fixes u.s.
	copy = re.sub(r'u\s\.\sk\s\.', r'U.K.', copy) # fixes u.k.
	copy = re.sub(r'd\s\.\sc\s\.', r'U.K.', copy) # fixes d.c.


	return copy

#########################################################
#########################################################
#########################################################

def unescape(str1):
	s = str1.replace("&amp;", "&")
	s = s.replace("&amp", "&")
	return s

#########################################################
#########################################################
#########################################################

def get_n_tweets(screen_name, n):
	#########################################################
	#Twitter API credentials
	consumer_key = "ThPs2SRcMr1apVG0CxpGKJFIx"
	consumer_secret = "GUsRVzhztAxjNu2T9MNrr4tOPPCxM9r6zu1LGR1JHkBTMrhcFV"
	access_key = "881327352-q78TpFwIkTmCwf4GTeDkQ98FTQcTtnYK8scYaJc8"
	access_secret = "SlvJOyjlpRfkIpe9qKEBcJdwudoVRjDENfHnj7T5Ufkeh"
	#########################################################

	#########################################################
	#authorize twitter, initialize tweepy
	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
	auth.set_access_token(access_key, access_secret)
	api = tweepy.API(auth)
	#########################################################

	fixed_tweets1 = list()

	try:
		for tweet in tweepy.Cursor(api.user_timeline, screen_name=screen_name, tweet_mode='extended', include_rts=False, count=n).items(n):
			fixed_tweet = str(tweet.full_text.encode('ascii',errors='ignore'))
			fixed_tweets1.append(fixed_tweet)

	except:
		print("Oops, could not get any tweets, try the program again")
		return 0

	return fixed_tweets1

#########################################################
#########################################################
#########################################################

def write_list_to_file(path_name, list1, username):
	if list1 != None:
		fixed_username = username[1:]

		file_name = path_name + fixed_username + ".txt"

		file1 = open(file_name, "w")

		file1.write(" * ")

		for each in list1:
			# each = tokenize_text(each)
			file1.write(each.encode("utf-8"))
			file1.write(" * ")

		return file_name

#########################################################
#########################################################
#########################################################

def file_input():
	input_file = raw_input("Where would you like the file to be written to? >>>\n")

	while input_file == "" or os.path.exists(input_file) == False:
		input_file = raw_input("Sorry, please enter a valid location >>>\n")

	return input_file

#########################################################
#########################################################
#########################################################

def twitter_handle_input():
	#########################################################
	#Twitter API credentials
	consumer_key = "ThPs2SRcMr1apVG0CxpGKJFIx"
	consumer_secret = "GUsRVzhztAxjNu2T9MNrr4tOPPCxM9r6zu1LGR1JHkBTMrhcFV"
	access_key = "881327352-q78TpFwIkTmCwf4GTeDkQ98FTQcTtnYK8scYaJc8"
	access_secret = "SlvJOyjlpRfkIpe9qKEBcJdwudoVRjDENfHnj7T5Ufkeh"
	#########################################################

	#########################################################
	#authorize twitter, initialize tweepy
	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
	auth.set_access_token(access_key, access_secret)
	api = tweepy.API(auth)
	#########################################################

	handle_input = raw_input("What Twitter Handle do you want a file for? >>>\n")

	correct_input = True
	exception_caught = False

	if handle_input == "":
		# print("empty handle")
		correct_input = False

	else:
		# print("handle isn't empty")
		try:
			for tweets in tweepy.Cursor(api.user_timeline, screen_name=handle_input, count=1).items(1):

				id = tweets.user.id

		#
		# print(tweets.text.lower().encode('ascii',errors='ignore'))
		except tweepy.error.TweepError:
			# print("user doesn't exist")
			exception_caught = True
			correct_input = False

	while correct_input == False:
		exception_caught = False
		# print("while-loop incorrect input")
		handle_input2 = raw_input("Sorry, please enter a valid Twitter handle >>>\n")
		try:
			for tweets in tweepy.Cursor(api.user_timeline, screen_name=handle_input2, count=1).items(1):

				id = tweets.user.id
		#
		# print(tweets.text.lower().encode('ascii',errors='ignore'))
		except tweepy.error.TweepError:
			# print("user doesn't exist")
			exception_caught = True
			correct_input = False

		if exception_caught != True and handle_input2 != "":
			# print("exit the while!")
			correct_input = True
			handle_input = handle_input2

	if handle_input[0] != "@":
		handle_input = "@" + handle_input

	return handle_input

#########################################################
#########################################################
#########################################################

def number_input():
	digits = list("1234567890")
	input_num = raw_input("What's the maximum # of tweets you want to gather? >>>\n")

	correct_input = True

	if input_num == "" or int(input_num) == 0:
		correct_input = False

	else:
		for each in input_num:
			if each not in digits:
				correct_input = False

	while correct_input == False:
		input_num = raw_input("Oops, enter a valid number >>>\n")
		if input_num != "" and int(input_num) != 0:
			correct_input = True
		for each in input_num:
			if each not in digits:
				correct_input = False

	return int(input_num)

#########################################################
#########################################################
#########################################################

def clean_tweets(list_tweets):
	copy = list_tweets[:]
	return_list = list()

	i = 0
	for each_tweet in copy:

		# done
		lowered = each_tweet.lower() # works

		# done
		fixed = unescape(lowered) # works # important for 2270

		# done
		fixed2 = re.sub("[;\"'()]","", fixed) # this works...

		final = tokenize_text(fixed2)

		return_list.append(final)

		i += 1

	return return_list

#########################################################
#########################################################
#########################################################

def handle_markov_input():
	markovOrder = raw_input("What Markov Order would you like generated? >>> ")
	while int(markovOrder) < 1 or int(markovOrder) > 5:
		markovOrder = raw_input("Oops, please enter a number 1-5 >>> ")
	return markovOrder

#########################################################
#########################################################
#########################################################

def main():
	space = " "

#########################################################

	print("")

	input_file = file_input()

	print("")

	input_twitter_handle = twitter_handle_input()

	print("")

	number_tweets = number_input()

	print("")


	print("---------------------------------------------------------------------------------")

	list_tweets = get_n_tweets(input_twitter_handle, number_tweets)

	print("")

	print("Total number of tweets collected: %d" % (len(list_tweets)))

	print("")

	cleaned_tweets = clean_tweets(list_tweets)

	file_name = write_list_to_file(input_file, cleaned_tweets, input_twitter_handle)

	print("---------------------------------------------------------------------------------")

	print("")

	markovOrder = handle_markov_input()

	print("")

	print("---------------------------------------------------------------------------------")

	# one way to do it lol
	# compile var
	# path = os.path.abspath('CLI\ Program\ copy/c++')
	# path = path.replace(' ', '\ ')
	# path = path.replace('\\\\', '\\')
	path = "c++/"
	compile = "g++ " + path + 'HashTable.cpp ' + path + 'ProductionWordGraphClass.cpp ' + path + 'MainDriver.cpp ' + path + 'TextTools.cpp ' + path + 'FileToString.cpp ' + path + 'AuthorStruct.cpp -std=c++11 -o Main'

	os.system(compile)

	random_message = True

	print("")

	user_input = raw_input("Hit enter to generate a random Tweet\nor N when you want a new Markov Order!\nor Q when you want to quit!").lower()

	print("")

	if user_input == "q":

		random_message = False

	else:

		random_message = True

	if user_input == "n":

		new_markov = True

	else:

		new_markov = False

	while random_message:

		if new_markov == True:

			print("---------------------------------------------------------------------------------")

			print("")

			markovOrder = handle_markov_input()

			print("")

			print("---------------------------------------------------------------------------------")

			new_markov = False

		executable = "./Main" + space + file_name + space + str(markovOrder)

		os.system(executable)

		user_input = raw_input("").lower()

		if user_input == "q":

			random_message = False

		if user_input == "n":

			new_markov = True




	# print("")

#########################################################
#########################################################
#########################################################

main()
