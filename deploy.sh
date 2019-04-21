#!/bin/bash -eu
mkdir -p docs
cd docs
rm -f deploy_key deploy_key.enc deploy.sh .travis.yml package.json
git init
git add .
git commit -m "Publishing site on `date "+%Y-%m-%d %H:%M:%S"`"
git push -f git@github.com:0918nobita/forth-book.git master:gh-pages
