# QML Gantt library

|    Linux      |  Windows   |
|:-------------:|:----------:|
| [![Build Status](https://travis-ci.org/dinusv/qml-gantt.svg?branch=master)](https://travis-ci.org/dinusv/qml-gantt)] | [![Build status](https://ci.appveyor.com/api/projects/status/dmstdr0ukobutitm/branch/master?svg=true)](https://ci.appveyor.com/project/dinusv/qml-gantt/branch/master) |



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

The `QGanttModel` class is an already implemented version of the ```QAbstractRangeModel``` class, therefore provides all the methods
required to communicate with the ```RangeView``` element. It's child items contain 3 properites: the **position** and **length**, 
which are used by the model to keep items sorted for easy access, and the **data** property, which is a variant type customizable by 
the user. It can contain any qml value type, or a reference to a QObject subclass, which can further extend the number of properties 
available. 

In the associated sample subproject, I've included the ```QGanttData``` class, which adds a color and label property to each gantt item.
The ```QGanttModel``` class is assigned a ```QGanttData``` object whenever a new ```QGanttModelItem``` is created and inserted in the model. This
is done internally by the model by calling a *configured* data factory function whenever an insertion is triggered. The function is configured
by using the ```QGanttModelItem::setItemDataFactoryFunction``` setter. The factory function is defined in the *sample/src/main.cpp* file.

To assign a different data item:

```cpp
class CustomData : public QObject{

    Q_OBJECT
    Q_PROPERTY(QString property1...)
    ...

}
```

we register the type to qml:

```cpp
qmlRegisterType<CustomData>("Gantt", 1, 0, "CustomData");
```


then define the item factory function:

```cpp
QVariant createModelData(){
    return QVariant::fromValue(new CustomData);
}
```

and register the function to our model:

```cpp
QGanttModel* model = new QanttModel;
model->setItemDataFactoryFunction(&createModelData);
```

then, whenever we invoke a new insertion, a ```CustomData``` type object will be set in the data field:

```cpp
model->insertItem(10, 10);
```

Which, in our delegate, can be accessed through the ```modelData``` property:

```qml
RangeView{
    ...
    delegate: Component{
        Text{ text: modelData.property1 }
    }
} 
```

The properties are set through simple assignments:

```qml
RangeView{
    ...
    delegate: Component{
        Rectangle{
            width: 200; height: 40;
            Text{ text: modelData.property1 }
            MouseArea{ anchors.fill: parent; onClicked: modelData.property1 = "new value"; }
        }
    }
} 
```


The *sample/resource/GanttLine.qml* file provides a full example on assignments and other item handling.

### Implementing the ```QAbstractRangeModel```

The  QAbstractRangeModel  and  QAbstractRangeModelIterator  provide the implementation 
requirements used by the  QRangeView  to work with the model data. The section is treated separately 
[here](doc/implement-qabstractrangemodel.md).
