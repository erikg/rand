Summary: A pipe utility that randomizes the stream.
Name: rand
Version: 1.8
Release: 1
Copyright: GPL
Vendor: Erik Greenwald
Url: http://math.smsu.edu/~br0ke/rand.html
Group: Applications/Text
Source0: http://math.smsu.edu/~br0ke/files/rand-1.8.tar.gz
Buildroot: /var/tmp/rand

%description
This program will take a file, input stream, or list of 'words' and repeat
them in a random order to the given output file or stdout. Kinda the opposite
of sort...

%prep
%setup -q
%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=/usr

make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
/usr/*

%changelog

