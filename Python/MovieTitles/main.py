# from hackerank
# given a json link display movie titles, if more than a page add &page=num to the link
# display them sorted

import urllib.request
import json

def fetchMovieTitles(keyword):
    url = "https://jsonmock.hackerrank.com/api/movies/search/?Title=" + keyword
    resp = urllib.request.urlopen(url)
    info = json.loads(resp.read())
    pages = info["total_pages"]
    movies = []
    for p in range(1, pages + 1):
        url = "https://jsonmock.hackerrank.com/api/movies/search/?Title=" + keyword + "&page=" + str(p)
        resp = urllib.request.urlopen(url)
        info = json.loads(resp.read())
        data = info['data']
        for d in data:
            movies.append(d['Title'])
    movies.sort()
    return movies



if __name__ == '__main__':
    movies = fetchMovieTitles("spider")
    for title in movies:
        print(title)

