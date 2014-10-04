##CSCI 104 Team Project Repository

###Student Information

**Developer 1**:
  + Name: Elif Naz Aydin
  + USC Email: eaydin@usc.edu
  + USC ID: 5695708139

**Developer 2**:
  + Name: Yoo Jin Lee
  + USC Email: yoojinl@usc.edu
  + USC ID: 3272884875

**Developer 3**:
  + Name: David Bell
  + USC Email: davidgbe@usc.edu
  + USC ID: 2476808567
  

###Project Information

####Please Compile with $ qmake then $ make in directory team_project_169/QT


**Part 1 - Advertising System**

In order to print out total computated bid value for each company, the user should close the application with __generated quit__ button, and avoid quitting the application by the 'x' quit button given in the window.

Elif Aydin worked on the ifstream part of reading advertisement files and storing them in a struct, while Yoo Jin (Grace) Lee worked on finding Set of Ads that match the keywords and apply Qt version for outputting and calculating bid values.

**Part 2 - Modified PR for Pages with Emphasize Keyword**

Part 1 of Part 2 of HW 10, We decided to the third option listed in the assignment. This part of the project was done by Yoo Jin (Grace) Lee.

>Implement more complete Markdown parsing of webpages, and use the information to improve PageRank. For instance, you could implement that if the search term(s) appear in bold or in headers, they are more important, and adjust the random jump probabilities. Or you could say that if a search term appears close to a link, that link should have higher weight (rather than 1/degree). Surely, you can come up with more such ideas. Again, this would be considered about full credit.

What we did was while parsing through the webpage, if the word is either in headers(#...) or __bold__ or *italic* then we would add the following words to emphSet of the webPage. Then when user enters keyword(s), program would iterate through all subset of WebPages with the keyword. While computing PageRank value of each WebPage, webPages where the keywords are emphasized will be given __(3/2)/n__ the probability, compared to others, with probability of 1/n, that are not emphasized in distributing remaining (a) fraction of webpages to every webPage in the subset.

Format for headers is a bit restrictive, in that we require the headers to be closed with another set of headers (#...) but each end of header does not have to match. We made closed headers required since the data set we were given does not really contain newlines, so closing the header would prevent the file from reading the entire file as emphasized words. Nested **bold** and _italics_ should have different symbol for either.

**Part 3 - Personalized Searches for Users with Accounts** 

Part 2 of Part 2: Second listed option in the assignment. This part was done by David Bell.

>Implement personalization. That is, users can have accounts, and the engine learns people's preferences over time. For instance, if you passed the first option and clicked on the second one instead, the system learns to show you the second one higher up next time, and not to show the first option. This information can also impact the PageRank computation, e.g., pages that you have clicked on get higher weight when the random surfer jumps away from the current page. This would be considered about full credit.

Users can created an account by typing in a username and password and pressing the 'new account' button. After logging in, searching will be customized to the user, with previous clicked links gaining additional relevance to queries they are mentioned in. Relevance is calibrated such that it will put a previous clicked link near the top of the list of results if the link is somewhat relevant to the search to begin with. Each click adds 1/num-pages-in-search to the existing pagerank value. 

Users' preferences are maintained so long as the program is running. You are free to log in and out without having to worry about tampering with each user's preferences. 

**Part 4 - Word Stemming** 

Part 4 of Part 2: First listed option in the assignment. 

>Implement sufficiently complete word stemming. That is, make sure that when a user searches for "enjoying", they are also shown matches for "enjoy", "enjoys", "enjoyed", etc. To calibrate you, this would be considered not quite full credit, but reasonably close, maybe 40% instead of 50%.

Elif Naz Aydin wrote the function findRoot to find the roots of the words and David Bell wrote the function wordsWithPrefix to generate similar words. Similar words are generated only if the user searches for a single word without using the AND/OR option.
 

