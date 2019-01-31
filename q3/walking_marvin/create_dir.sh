if [ ! -d "$1" ]; then
  mkdir $1
fi
if [ ! -d "$1/$2" ]; then
  mkdir $1/$2
fi
if [ ! -d "$1/$2/$3" ]; then
  mkdir $1/$2/$3
fi
