#include "myscene.h"
#include "line.h"
#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include <QCursor>

MyScene::MyScene(QObject *parent):
    QGraphicsScene(parent)
{
    setFocus();
    Figure=Move;
    line=nullptr;
    myline=nullptr;
    isDrawSquad = false;
}
MyScene::~MyScene()
{}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)//------------------------------------------------------------------------------------------------------------------
{//qDebug()<<"MyScene::mousePressEvent";
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    mouseLeftButtonPress=true;
    switch(Figure)
    {
    case InsertLine:
        //qDebug()<<"MousePress_Line";
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos()));
        line->setPen(QPen(myLineColor, 2));
        addItem(line);
        break;
    case setResistor:
        //qDebug()<<"MousePress_Kvadrat";
        if(countResistor==0)
        {item=resistorobj;}
        else{
            item = new ResistorClass(resistorobj->rowindatabase,countResistor,resistorobj->Marking,resistorobj->Resistortype,resistorobj->Resistance,
                                     resistorobj->Power,resistorobj->Typeofshell,resistorobj->Length,
                                     resistorobj->Wight,resistorobj->Height,resistorobj->Thicknessofleg);}
        qDebug()<<"scene="<<resistorobj->Marking<<" "<<resistorobj->Resistortype<<" "<<resistorobj->Resistance<<
                  " "<<resistorobj->Power<<" "<<resistorobj->Typeofshell<<" "<<resistorobj->Length<<
                  " "<<resistorobj->Wight<<" "<<resistorobj->Height<<" "<<resistorobj->Thicknessofleg;
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        radioelements.push_back(item);
        listText.push_back(item->text);
        countResistor++;
        qDebug()<<"countResistor = "<<countResistor;
        break;
    case setCondensator:
        if(countCondensator==0)
        {item=condensatorobj;}
        else{
            item = new CondensatorClass(countCondensator,condensatorobj->Marking,condensatorobj->Capacitortype,condensatorobj->Capacity,
                                        condensatorobj->Typeofshell,condensatorobj->Length,
                                        condensatorobj->Wight,condensatorobj->Height,condensatorobj->Thicknessofleg);}
        qDebug()<<"scene="<<condensatorobj->Marking<<" "<<condensatorobj->Capacitortype<<" "<<condensatorobj->Capacity<<
                  " "<<condensatorobj->Typeofshell<<" "<<condensatorobj->Length<<" "<<condensatorobj->Wight
               <<" "<<condensatorobj->Height<<" "<<condensatorobj->Thicknessofleg;
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        radioelements.push_back(item);
        listText.push_back(item->text);
        countCondensator++;
        break;
    case setDiode:
        if(countDiode==0)
        {item=diodeobj;}
        else{
            item = new DiodeClass(countDiode,diodeobj->Marking,diodeobj->Diodetype,diodeobj->Breackdownvoltage,
                                  diodeobj->Typeofshell,diodeobj->Length,
                                  diodeobj->Wight,diodeobj->Height,diodeobj->Thicknessofleg);}
        qDebug()<<"scene="<<diodeobj->Marking<<" "<<diodeobj->Diodetype<<" "<<diodeobj->Breackdownvoltage<<
                  " "<<diodeobj->Typeofshell<<" "<<diodeobj->Length<<" "<<diodeobj->Wight
               <<" "<<diodeobj->Height<<" "<<diodeobj->Thicknessofleg;
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        radioelements.push_back(item);
        listText.push_back(item->text);
        countDiode++;
        break;
    case setTransistor:
        if(countTransistor==0)
        {item=transistorobj;}
        else{
            item = new TransistorClass(countTransistor,transistorobj->Marking,transistorobj->Transistortype,transistorobj->Structure,
                                       transistorobj->Typeofshell,transistorobj->Length,
                                       transistorobj->Wight,transistorobj->Height,transistorobj->Thicknessofleg);}
        qDebug()<<"scene="<<transistorobj->Marking<<" "<<transistorobj->Transistortype<<" "<<transistorobj->Structure<<
                  " "<<transistorobj->Typeofshell<<" "<<transistorobj->Length<<" "<<transistorobj->Wight
               <<" "<<transistorobj->Height<<" "<<transistorobj->Thicknessofleg;
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        radioelements.push_back(item);
        listText.push_back(item->text);
        countTransistor++;
        break;
    case Move:

        //qDebug()<<"PressEvent1";
        int itemundermouse=0;
        foreach(QGraphicsItem* sceneitems, this->items())
        {if(sceneitems->isUnderMouse()==true)
            {itemundermouse++;}
        }
        if(itemundermouse==0)
        {

        }
        qDebug()<<"PressEvent2";

        if(!listText.isEmpty())//чтобы снимать редактирование с текста
        { for(int i=0;i<listText.count();i++)
            {if(!listText.at(i)->isSelected())
                {listText.at(i)->setTextInteractionFlags(Qt::NoTextInteraction);}
            }
        }

        //qDebug()<<"PressEvent3";

        selectedRadioelements=selectedItems().count();
        for(int i=0;i<selectedItems().count();i++)
        {if(selectedItems().at(i)->type()==65538)
            {selectedRadioelements--;}
        }
        //qDebug()<<"PressEvent4";
        positionMouse = mouseEvent->scenePos();
        if(myline!=nullptr && Figure==Move && mouseLeftButtonPress==true && selectedrubber==false)
        {
            for(int i=0;i<listLine.count();i++)
            {
                if(listLine.at(i)->isSelected())
                {   mouseCoordinateOffset=mouseEvent->scenePos()-positionMouse;
                    listLine.at(i)->PointSelectionControl();
                }
            }
        }
        //qDebug()<<"PressEvent5";
        if(myline!=nullptr && mouseEvent->modifiers() & Qt::ControlModifier)
        {
            for(int i=0;i<listLine.count();i++){if(listLine.at(i)->isSelected()){listLine.at(i)->PushedControlModifier(mouseEvent->scenePos());}}
        }
        //qDebug()<<"selectedrubber1 = "<<selectedrubber;
        if(!radioelements.isEmpty() && Figure==Move && mouseLeftButtonPress==true && selectedrubber==false)
        {//qDebug()<<"!radioelements.isEmpty() && Figure==Move && mouseLeftButtonPress==true && selectedrubber==false";
            for(int i=0;i<radioelements.count();i++)
            {   if(radioelements.at(i)->isSelected())
                {  radioelements.at(i)->setMoveFlag(true);}
            }
        }

        break;
    }
    //qDebug()<<"PressEvent6";
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)//------------------------------------------------------------------------------------------------------------------------
{//qDebug()<<"MyScene::mouseMoveEvent";
    if (Figure==InsertLine && line != nullptr)
    {   //qDebug()<<"MouseMove_Line";
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }

    if(Figure==Move && mouseLeftButtonPress==true && selectedrubber==true)
    {//qDebug()<<"MovecreateSelectedRect";
        if(!radioelements.isEmpty()){
            for(int i=0;i<radioelements.count();i++)
            {
                radioelements.at(i)->setMoveFlag(false);
            }
        }

        selectedRadioelements=selectedItems().count();
        for(int i=0;i<selectedItems().count();i++)
        { if(selectedItems().at(i)->type()==65538)
            {  selectedRadioelements--;}
        }

    }
    //qDebug()<<"MyScene::mouseMoveEvent1";

    //qDebug()<<"MyScene::mouseMoveEvent2";
    if(Figure==Move && mouseLeftButtonPress==true  && selectedrubber==false && !listLine.isEmpty())
    {
        //qDebug()<<"Figure==Move && mouseLeftButtonPress==true && selectedItems().count()>1 && myline!=nullptr && selectedrect==nullptr";
        //myline->setFlag(QGraphicsItem::ItemIsMovable);
        //myline->setPos(mouseEvent->scenePos());
        if(!listLine.isEmpty())
        {for(int i=0;i<listLine.count();i++)
            {if(listLine.at(i)->isSelected())
                {
                    mouseCoordinateOffset=mouseEvent->scenePos()-positionMouse;
                    if(mouseEvent->modifiers() != Qt::ShiftModifier)
                    {listLine.at(i)->MoveFullLine(mouseCoordinateOffset);}
                    listLine.at(i)->MoveSegmentLine(mouseEvent->scenePos());
                }
            }
        }
    }
    // qDebug()<<"MyScene::mouseMoveEvent3";
    if(!listLine.isEmpty() && Figure==Move && mouseLeftButtonPress==true && selectedrubber==false)
    {for(int i=0;i<listLine.count();i++)
        {
            if(listLine.at(i)->listelements.at(0)!=NULL)
            {if(mouseEvent->modifiers() & Qt::ShiftModifier && listLine.at(i)->myStartItem->isSelected() && listLine.at(i)->listpointer.count()==2)
                {qDebug()<<"ItemIsMovable,false";listLine.at(i)->shiftpush(true);listLine.at(i)->myStartItem->setFlag(QGraphicsItem::ItemIsMovable,false);
                }
            }
            if(listLine.at(i)->listelements.at(1)!=NULL)
            {if(mouseEvent->modifiers() & Qt::ShiftModifier && listLine.at(i)->myEndItem->isSelected() && listLine.at(i)->listpointer.count()==2)
                {qDebug()<<"ItemIsMovable,false";listLine.at(i)->shiftpush(true);listLine.at(i)->myEndItem->setFlag(QGraphicsItem::ItemIsMovable,false);
                }
            }
        }
    }
    //qDebug()<<"MyScene::mouseMoveEvent4";
    //qDebug()<<"selectedrubber2 = "<<selectedrubber;
    if(!radioelements.isEmpty() && Figure==Move && mouseLeftButtonPress==true && selectedrubber==false)
    {
        for(int i=0;i<radioelements.count();i++)
        {if(radioelements.at(i)->isSelected())
            {radioelements.at(i)->setMoveFlag(true);}
        }
    }

    //qDebug()<<"MyScene::mouseMoveEvent5";
    if(Figure==Move || Figure==setResistor || Figure==setCondensator || Figure==setDiode || Figure==setTransistor)
    {//qDebug()<<"MyScene::mouseMoveEvent";
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        update();
    }
    //qDebug()<<"MouseMove_Event";
    // qDebug()<<"MyScene::mouseMoveEvent6";
    if(!listLine.isEmpty() && !radioelements.isEmpty() && selectedrubber==false)
    {//qDebug()<<"collidesWithItem";
        foreach(MyLine* listmyline,listLine)
        {
            if(listmyline->isSelected())
            {foreach(ElementItem* listitem, radioelements)
                {//qDebug()<<"collidesWithItem2";
                    //qDebug()<<radioelements.count();
                    for(int i=0;i<listitem->listDotElements.count();i++)
                    {//qDebug()<<"collidesWithItem2.1";
                        if(!listmyline->listDotes.isEmpty() && listmyline->startItem()==nullptr && listmyline->StartDot()->collidesWithItem(listitem->listDotElements.at(i))==true)
                        {   //qDebug()<<"collidesWithItem3";
                            listmyline->AddAncorStartElements(listitem);
                        }//qDebug()<<"collidesWithItem2.2";
                        if(!listmyline->listDotes.isEmpty() && listmyline->endItem()==nullptr && listmyline->EndDot()->collidesWithItem(listitem->listDotElements.at(i))==true)
                        {   //qDebug()<<"collidesWithItem4";
                            listmyline->AddAncorEndElements(listitem);
                        }
                    }
                }
            }
        }
    }
    //qDebug()<<"MyScene::mouseMoveEvent7";
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)//----------------------------------------------------------------------------------------------------------------
{qDebug()<<"MyScene::mouseReleaseEvent";

    //qDebug()<<"MyScene::mouseReleaseEvent2";
    if(!listLine.isEmpty())
    {
        for(int i=0;i<listLine.count();i++)
        {
            if(listLine.at(i)->isSelected())
            {//qDebug()<<"UpdateListpointerUnderstudy()";
                listLine.at(i)->UpdateListpointerUnderstudy();
            }
        }
    }
    //qDebug()<<"MyScene::mouseReleaseEvent3";
    selectedRadioelements=selectedItems().count();
    for(int i=0;i<selectedItems().count();i++)
    {if(selectedItems().at(i)->type()==65538)
        {selectedRadioelements--;}
    }


    if(!radioelements.isEmpty() && Figure==Move  && selectedrubber==false)
    {//qDebug()<<"!radioelements.isEmpty() && Figure==Move  && selectedrubber==false";
        for(int i=0;i<radioelements.count();i++)
        {//if(radioelements.at(i)->isSelected())
            radioelements.at(i)->setMoveFlag(false);
            radioelements.at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
        }
    }
    //qDebug()<<"MyScene::mouseReleaseEvent4";
    if (Figure == InsertLine && line != nullptr)
    {
        QList<QGraphicsItem *>startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();

        QList<QGraphicsItem *>endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        sp1.setX(line->line().p1().x());
        sp1.setY(line->line().p1().y());
        ep1.setX(line->line().p2().x());
        ep1.setY(line->line().p2().y());

        removeItem(line);
        delete line;

        if(startItems.count() == 0 && endItems.count() == 0)
        {   myline = new MyLine(sp1,ep1);
            addItem(myline);
            listLine.push_back(myline);
            myline->setZValue(1000.0);
        }

        if(startItems.count() > 0 && endItems.count() == 0)
        {
            if(startItems.first()->type()==65537)
            {
                ElementItem *startItem = qgraphicsitem_cast<ElementItem *>(startItems.first());
                myline = new MyLine(startItem,sp1,ep1);
                addItem(myline);
                listLine.push_back(myline);
                startItem->addArrow(myline);
                myline->setZValue(-1000.0);
            }
        }

        if(startItems.count() == 0 && endItems.count() > 0)
        {
            if(endItems.first()->type()==65537)
            {   ElementItem *endItem = qgraphicsitem_cast<ElementItem *>(endItems.first());
                myline = new MyLine(sp1,ep1,endItem);
                addItem(myline);
                listLine.push_back(myline);
                endItem->addArrow(myline);
                myline->setZValue(-1000.0);

            }
        }
        //qDebug()<<"MyScene::mouseReleaseEvent5";
        if (startItems.count() > 0 && endItems.count() > 0 &&  startItems.first() != endItems.first())
        {
            if(startItems.first()->type()==65537 && endItems.first()->type()==65537)
            {
                ElementItem *startItem = qgraphicsitem_cast<ElementItem *>(startItems.first());
                ElementItem *endItem = qgraphicsitem_cast<ElementItem *>(endItems.first());
                myline = new MyLine(startItem,endItem,sp1,ep1);
                addItem(myline);
                listLine.push_back(myline);
                startItem->addArrow(myline);
                endItem->addArrow(myline);
                myline->setZValue(-1000.0);

            }
        }
        //qDebug()<<"MyScene::mouseReleaseEvent6";
        if (startItems.count() > 0 && endItems.count() > 0 &&  startItems.first() != endItems.first())
        {
            if(startItems.first()->type()==65538 && endItems.first()->type()==65538)
            {
                DotSignal *dotstartItem = qgraphicsitem_cast<DotSignal *>(startItems.first());
                DotSignal *dotendItem = qgraphicsitem_cast<DotSignal *>(endItems.first());
                myline = new MyLine(dotstartItem,dotendItem,sp1,ep1);
                addItem(myline);
                listLine.push_back(myline);
                ElementItem *TransStartItem = qgraphicsitem_cast<ElementItem *>(dotstartItem->parentItem());
                ElementItem *TransEndItem = qgraphicsitem_cast<ElementItem *>(dotendItem->parentItem());
                TransStartItem->addArrow(myline);
                TransEndItem->addArrow(myline);
                myline->setZValue(-1000.0);

            }
        }
        //qDebug()<<"MyScene::mouseReleaseEvent7";
        if (startItems.count() > 0 && endItems.count() > 0 &&  startItems.first() != endItems.first())
        {
            if(startItems.first()->type()==65537 && endItems.first()->type()==65538)
            {
                ElementItem *startItem = qgraphicsitem_cast<ElementItem *>(startItems.first());
                DotSignal *dotendItem = qgraphicsitem_cast<DotSignal *>(endItems.first());
                myline = new MyLine(startItem,dotendItem,sp1,ep1);
                addItem(myline);
                listLine.push_back(myline);
                ElementItem *TransEndItem = qgraphicsitem_cast<ElementItem *>(dotendItem->parentItem());
                startItem->addArrow(myline);
                TransEndItem->addArrow(myline);
                myline->setZValue(-1000.0);
            }
        }
        //qDebug()<<"MyScene::mouseReleaseEvent8";
        if (startItems.count() > 0 && endItems.count() > 0 && startItems.first() != endItems.first())
        {
            if(startItems.first()->type()==65538 && endItems.first()->type()==65537)
            {
                DotSignal *dotstartItem = qgraphicsitem_cast<DotSignal *>(startItems.first());
                ElementItem *endItem = qgraphicsitem_cast<ElementItem *>(endItems.first());
                myline = new MyLine(dotstartItem,endItem,sp1,ep1);
                addItem(myline);
                listLine.push_back(myline);
                ElementItem *TransStartItem = qgraphicsitem_cast<ElementItem *>(dotstartItem->parentItem());
                TransStartItem->addArrow(myline);
                endItem->addArrow(myline);
                myline->setZValue(-1000.0);
            }
        }
        //qDebug()<<"MyScene::mouseReleaseEvent9";
        if (startItems.count() > 0 && endItems.count() == 0)
        {
            if(startItems.first()->type()==65538)
            {
                DotSignal *dotstartItem = qgraphicsitem_cast<DotSignal *>(startItems.first());
                myline = new MyLine(dotstartItem,sp1,ep1);
                addItem(myline);
                listLine.push_back(myline);
                ElementItem *TransStartItem = qgraphicsitem_cast<ElementItem *>(dotstartItem->parentItem());
                TransStartItem->addArrow(myline);
                myline->setZValue(-1000.0);
            }
        }

        if (startItems.count() == 0 && endItems.count() > 0)
        {
            if(endItems.first()->type()==65538)
            {
                DotSignal *dotendItem = qgraphicsitem_cast<DotSignal *>(endItems.first());
                myline = new MyLine(sp1,ep1,dotendItem);
                addItem(myline);
                listLine.push_back(myline);
                ElementItem *TransEndItem = qgraphicsitem_cast<ElementItem *>(dotendItem->parentItem());
                TransEndItem->addArrow(myline);
                myline->setZValue(-1000.0);
            }
        }
        line = nullptr;
    }
    mouseLeftButtonPress=false;
    //qDebug()<<"MyScene::mouseReleaseEvent10";
    if(!listLine.isEmpty())
    {
        for(int i=0;i<listLine.count();i++)
        {
            listLine.at(i)->setFlag_vertical(false);
            listLine.at(i)->setFlag_horizontal(false);
            listLine.at(i)->setFlag_popadanie_vertical(false);
            listLine.at(i)->setFlag_popadanie_horizontal(false);
            listLine.at(i)->setFlag_start_horizontal(false);
            listLine.at(i)->setFlag_start_vertical(false);
            listLine.at(i)->setFlag_end_horizontal(false);
            listLine.at(i)->setFlag_end_vertical(false);
            listLine.at(i)->setFlag_hoverenter(false);
            listLine.at(i)->LineAjustment();
        }
    }
    //qDebug()<<"MyScene::mouseReleaseEven11";
    Q_UNUSED(mouseEvent);
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


void MyScene::on_Rotate_clockwise_triggered()
{
    foreach(ElementItem* listitem, radioelements)
    {
        if(listitem->isSelected())
        {
            listitem->setAngle(listitem->GetAngle()+90);
            listitem->setRotation(listitem->GetAngle());
            listitem->text->setRotation(-(listitem->GetAngle()));
            listitem->text->setPos(listitem->rotateText(listitem->text->pos(),-90));
        }
    }
    update();
}
void MyScene::Set_Rotate_Elementn_on_Load(ElementItem *item,qreal angle)
{
    item->setAngle(angle);
    item->setRotation(item->GetAngle());
    item->text->setRotation(-(item->GetAngle()));
    if(angle==0){return;}
    if(angle>0)
    {for(int i=0;i<angle;i+=90)
        {qDebug()<<i;item->text->setPos(item->rotateText(item->text->pos(),-90));}
    }
    if(angle<0)
    {for(int i=0;i<angle;i-=90)
        {qDebug()<<i;item->text->setPos(item->rotateText(item->text->pos(),+90));}
    }
}
void MyScene::on_Rotae_counterclockwise_triggered()
{
    foreach (ElementItem* listitem, radioelements)//Поворачиваем
    {
        if(listitem->isSelected())
        {
            listitem->setAngle(listitem->GetAngle()-90);
            listitem->setRotation(listitem->GetAngle());
            listitem->text->setRotation(-(listitem->GetAngle()));
            listitem->text->setPos(listitem->rotateText(listitem->text->pos(),90));
        }
    }
    update();
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    if(item && Figure==Move && isDrawSquad == false)
    {
        qDebug()<<"keyPressEvent";
        //event->modifiers() = Qt::NoModifier;
        //if (event->modifiers() == Qt::ControlModifier)
        //         switch (event->key())
        //         {qDebug()<<"keyPressEventSWICH";
        //         case Qt::Key_Up: angle += 90; break; //Ctrl+Стрелка вверх
        //         case Qt::Key_Down: angle -= 90; break; //Ctrl+Стрелка вниз
        //         default: angle = -1; break;
        //         }

    }

    if (event->modifiers() == Qt::ControlModifier)
    {
        qDebug()<<"CRTL_pushed";
        if(!listLine.isEmpty())
        {qDebug()<<"CRTL_pushed2";
            foreach(MyLine* itemline, listLine)
            {
                if(itemline->isSelected())
                {itemline->ctrlpush(true);}
            }
        }
        //Ctrlpushed=true;
    }

    if (event->modifiers() == Qt::ShiftModifier)
    {
        //qDebug()<<"SHIFT_pushed";
        if(!listLine.isEmpty())
        {//qDebug()<<"SHIFT_pushed2";
            foreach(MyLine* itemline, listLine)
            {//qDebug()<<"SHIFT_pushed3";
                if(itemline->isSelected())
                {itemline->shiftpush(true);}
                //qDebug()<<"SHIFT_pushed4";
                if(itemline->listelements.at(0)!=NULL)
                {if(itemline->myStartItem->isSelected())
                    {itemline->shiftpush(true);
                    }
                }//qDebug()<<"SHIFT_pushed5";
                if(itemline->listelements.at(1)!=NULL)
                {if(itemline->myEndItem->isSelected())
                    {itemline->shiftpush(true);
                    }
                }qDebug()<<"SHIFT_pushed6";
            }
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Control)
    {
        qDebug()<<"CRTL_Release";
        if(!listLine.isEmpty())
        {myline->ctrlpush(false);}
    }

    if (event->key()==Qt::Key_Shift)
    {
        qDebug()<<"SHIFT_Release";

        foreach(MyLine* itemline, listLine)
        {
            if(itemline->isSelected())
            {itemline->shiftpush(false);}
            if(itemline->listelements.at(0)!=NULL && itemline->myStartItem->isSelected())
            {itemline->shiftpush(false);}
            if(itemline->listelements.at(1)!=NULL && itemline->myEndItem->isSelected())
            {itemline->shiftpush(false);}
        }

    }
    QGraphicsScene::keyReleaseEvent(event);
}

void MyScene::on_action_Delete_triggered()
{
    //QList<QGraphicsItem*> selected = selectedItems();
    for(int i=0;i<selectedItems().count();i++)
    {
        qDebug()<<"DEL_cycle";
        if(!radioelements.isEmpty())
        {
            for(int i=0;i<radioelements.count();i++)
            {qDebug()<<"DEL_cycle1";
                if(radioelements.at(i)->isSelected())
                {qDebug()<<"DEL_cycle2";
                    if(radioelements.at(i)->typeElement==ElementItem::RESISTOR)
                    {countResistor--;}
                    if(radioelements.at(i)->typeElement==ElementItem::CONDENSATOR)
                    {countCondensator--;}
                    if(radioelements.at(i)->typeElement==ElementItem::DIODE)
                    {countDiode--;}
                    if(radioelements.at(i)->typeElement==ElementItem::TRANSISTOR)
                    {countTransistor--;}

                    for(int j=0;j<radioelements.at(i)->arrows.count();j++)
                    {if(radioelements.at(i)->isSelected()==true && radioelements.at(i)==radioelements.at(i)->arrows.at(j)->myStartItem)
                        {radioelements.at(i)->arrows.at(j)->deleteStartAncorElements();}

                        if(radioelements.at(i)->isSelected()==true && radioelements.at(i)==radioelements.at(i)->arrows.at(j)->myEndItem)
                        {radioelements.at(i)->arrows.at(j)->deleteEndAncorElements();}
                    }
                    qDebug()<<"DEL_cycle2.6";
                    if(listText.indexOf(radioelements.at(i)->text)>=0)
                        listText.removeAt(listText.indexOf(radioelements.at(i)->text));//}
                }
                for(int j=0;j<radioelements.at(i)->arrows.count();j++)
                {if(radioelements.at(i)->isSelected()==false && radioelements.at(i)==radioelements.at(i)->arrows.at(j)->myStartItem && radioelements.at(i)->arrows.at(j)->isSelected())
                    {radioelements.at(i)->arrows.at(j)->deleteStartAncorElements();}

                    if(radioelements.at(i)->isSelected()==false && radioelements.at(i)==radioelements.at(i)->arrows.at(j)->myEndItem && radioelements.at(i)->arrows.at(j)->isSelected())
                    { radioelements.at(i)->arrows.at(j)->deleteEndAncorElements();}
                }
            }
        }
        qDebug()<<"DEL_cycle3";
        if(!listLine.isEmpty())
        {
            for(int i=0;i<listLine.count();i++)
            {
                if(listLine.at(i)->isSelected())
                {
                    if(listLine.at(i)->listelements.at(0)!=NULL && listLine.at(i)->listelements.at(0)->type()==65537)
                    {ElementItem *ThisItem = qgraphicsitem_cast<ElementItem *>(listLine.at(i)->listelements.at(0));
                        ThisItem->removeArrow(listLine.at(i)); qDebug()<<"DEL_cycle_ArrowsDel1";
                    }
                    if(listLine.at(i)->listelements.at(0)!=NULL && listLine.at(i)->listelements.at(0)->type()==65538)
                    {   ElementItem *ThisItem = qgraphicsitem_cast<ElementItem *>(listLine.at(i)->listelements.at(0)->parentItem());
                        ThisItem->removeArrow(listLine.at(i)); qDebug()<<"DEL_cycle_ArrowsDel2";
                    }
                    if(listLine.at(i)->listelements.at(1)!=NULL && listLine.at(i)->listelements.at(1)->type()==65537)
                    {   ElementItem *ThisItem = qgraphicsitem_cast<ElementItem *>(listLine.at(i)->listelements.at(1));
                        ThisItem->removeArrow(listLine.at(i)); qDebug()<<"DEL_cycle_ArrowsDel3";
                    }
                    if(listLine.at(i)->listelements.at(1)!=NULL && listLine.at(i)->listelements.at(1)->type()==65538)
                    {   ElementItem *ThisItem = qgraphicsitem_cast<ElementItem *>(listLine.at(i)->listelements.at(1)->parentItem());
                        ThisItem->removeArrow(listLine.at(i)); qDebug()<<"DEL_cycle_ArrowsDel4";
                    }

                }
            }
        }
        qDebug()<<"DEL_cycle4";
        for(int i=0;i<radioelements.count();i++)
        {qDebug()<<"DEL_cycle5";
            if(radioelements.at(i)->isSelected())
            {
                this->removeItem(radioelements.at(i));
                delete radioelements.at(i);
                radioelements.removeAt(i);
            }
        }
        for(int i=0;i<listLine.count();i++)
        {qDebug()<<"DEL_cycle6";
            if(listLine.at(i)->isSelected())
            {
                this->removeItem(listLine.at(i));
                delete listLine.at(i);
                listLine.removeAt(i);
                myline=nullptr;
            }
        }
        qDebug()<<"DEL_cycle7";
    }
    qDebug()<<"DEL_cycle8";
}

void MyScene::SetFlagSelectionRect(bool b)
{
    selectedrubber=b;

}

void MyScene::on_pBtn_Move_clicked()
{
    Figure=Move;
    isDrawSquad = false;
    qDebug()<<"pushButton_Move";
}

