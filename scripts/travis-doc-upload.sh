#!/bin/sh

set -e

eval key=\$encrypted_${SSH_KEY_TRAVIS_ID}_key
eval iv=\$encrypted_${SSH_KEY_TRAVIS_ID}_iv

mkdir -p ~/.ssh
mv scripts/id_rsa ~/.ssh/id_rsa
chmod 600 ~/.ssh/id_rsa

git clone git@github.com:Martindev/martock.git
cd martock
git config user.name "Martbot"
git config user.email "Martbot@martbot"
git checkout gh-pages

rm -rf doc
mv ../target/doc .
git add -u
git add doc

git commit -m "martock doc hook"
git push origin gh-pages
