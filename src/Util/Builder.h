//Builder interface
#ifndef SRC_BUILDER_H
#define SRC_BUILDER_H

template <class T> class IBuilder{
public:
	virtual ~IBuilder(){} ;
	virtual T build() = 0;
};

#endif  //SRC_BUILDER_H
