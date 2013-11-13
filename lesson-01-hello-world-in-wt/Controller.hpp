#pragma once

/*
 * =====================================================================================
 *
 *       Filename:  Controller.hpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/08/13 18:15:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ltase Damasked (), lyase.d@gmail.com
 *        Company:
 * =====================================================================================
 */

#include "IObservers.hpp"
#include "IController.hpp"
#include "IBeatModel.hpp"
#include "IView.hpp"
#include "IObservers.hpp"
#include"ModelObserver.h"
#include <vector>
#include <cassert>
#include <functional>
#include <iostream>


using Views = std::vector<IView*>;

class Controller : public IController, public IController4View {
private:
     Views views;
     pIBeatModel model;
     ModelObserver observer;
public:
     Controller(pIBeatModel model)
          : IController(), views {}, model {model}, observer {model, views} {
          model->initialize();
     }
     virtual void start() override {
          assert(views.size() > 0);
          model->on();
for (auto view : views)
               view->createView();
     }
     virtual void stop() override {
          model->off();
     }
     virtual void addView(IView* view) override {
          views.push_back(view);
     }
     // Methods called by the view
     virtual void increaseBPM() override {
          auto bpm = model->getBPM();
          model->setBPM(bpm+1);
     }
     virtual void decreaseBPM() override {
          auto bpm = model->getBPM();
          model->setBPM(bpm-1);
     }
     /// The view is telling us that the BPM has changed.
     /// We will update the model, which will update all of the views
     virtual void setBPM(int bpm) override {
          model->setBPM(bpm);
     }
};

