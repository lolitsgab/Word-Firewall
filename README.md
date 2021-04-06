# Word-Firewall

This is a filter that will take any size word file and identify bad words from a given list. Another list can be given to propose replacement of those words to the culprit.

It uses a bloom-filter as the main way to quickly find if a word is a culprit or not.
