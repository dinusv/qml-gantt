# QML Gantt library

[![Build Status](https://travis-ci.org/dinusv/qml-gantt.svg?branch=master)](https://travis-ci.org/dinusv/qml-gantt)

An efficient implementation of a gantt chart library for qml. The library provides a custom View element
which handles lazy loading of items according to its viewport. Items are loaded from a model which can 
easily be implemented according to custom specifications.

 * **Version**: 0.1.0
 * **License**: LPGL
 * **Library requirements**: Qt5 or higher
 * **Sample project requirements**: Qt5.3 or higher

A fully editable gantt chart element is provided in the associated sample project:

 ![Gantt sample screen shot](/doc/screen-gantt.png)

## Usage

The project can be used as an externally linked library or by including the source files directly. (The first option would be the preferred one).

### Compiling the library

 * Download the source code
 * Run the following command within the project directory to generate the library:
 
```
    cd build
    qmake -r ..
    make (or nmake)
```

 * The library will be available within the build directory. You can run the associated gantt example project from the sample directory:

```
	sample/./sample	
```

 * Or you can link to the library from your own project and implement the model data:

```
    INCLUDEPATH += $$GANTTLIBPATH/include
	
    LIBS += -L$$GANTTLIBPATH/lib -lqmlgantt
```

### Manually including the source files

 * Download the source code
 * Include the following files into your project:
    * qganttglobal
    * qabstractrangemodel.h
    * qabstractrangemodel.cpp
    * qrangeview.h
    * qrangeview.cpp
    * qganttmodel.h
    * qganttmodel.cpp
    * qganttmodelitem.h
    * qganttmodelitem.cpp
 * Implement the model data and you're ready to go


## Implementing the model data

There are two ways to add custom data through the model:

 * Adding a ```QGanntModel``` item (the easy way)
 * Implementing your own model by extending the ```QAbstractRangeModel``` (the custom way and also the bit more difficult one)

### Adding a ```QGanntModel``` data item

The `QGanttModel` class already provides all the methods required to communicate with the `RangeView` element.
Its items are ordered in ascending order according to their position.  

### Implementing the ```QAbstractRangeModel```

The ```QAbstractRangeModel``` and ```QAbstractRangeModelIterator``` provide the implementation requirements
used by the ```QRangeView``` to work with the model data. 

The ```QRangeView``` does not need to know the number of items contained within the model. The indexes are also
not required, therefore items within the model can be stored in linked-lists, trees or other container types.

The view accesses items only through their positions, so it is important for the view to know the total content
length of the model. This is given by the ```contentLength()``` method. Changes in the model are notified by 
item positions. 
