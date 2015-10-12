# QML Gantt library
 
An efficient implementation of a gantt chart library for qml. The library provides a custom View element
which handles lazy loading of items according to its viewport. Items are loaded from a model which can easily be implemented according to custom specifications.

 * **Version**: 0.1.0
 * **License**: LPGL
 * **Compatiblity**: Qt5 or higher

The sample associated provides an editable gantt chart element like below:

 ![Gantt sample screen shot](/doc/screen-gantt.jpg)

## Usage

The project can be used as an externally linked library or by including the source files directly. (The first version would be the preferred one).

### Compiling and linking to the library

 * Download the source code
 * Run the following command within the project directory to generate the library:
 
```
    cd build
    qmake ..
    make (or nmake)
```

 * Run the sample file, or link to the library from other projects, and implement the model data:
 
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
 * Implementing your own model by extending the ```QAbstractRangeModel``` (the harder or custom way)

### Adding a ```QGanntModel``` item


### Implementing the ```QAbstractRangeModel```

The ```QAbstractRangeModel``` and ```QAbstractRangeModelIterator``` provide the implementation requirements
used by the ```QRangeView``` to work with the model data. 

The ```QRangeView``` does not need to know the number of items contained within the model. The indexes are also
not required, therefore items within the model can be stored in linked-lists, trees or other container types.

The view accesses items only through their positions, so it is important for the view to know the total content
length of the model. This is given by the ```contentLength()``` method. Changes in the model are notified by 
item positions. 
