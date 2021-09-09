import { NgModule } from '@angular/core';
import { CommonModule, } from '@angular/common';
import { BrowserModule  } from '@angular/platform-browser';
import { Routes, RouterModule } from '@angular/router';

import { AdminLayoutComponent } from './layouts/admin-layout/admin-layout.component';
import { RamComponent } from './ram/ram.component';
import { ProcesosComponent } from './procesos/procesos.component';
import { KillpComponent } from './killp/killp.component';

const routes: Routes =[
  {path:'procesos', component:ProcesosComponent},
  {
    path: '',
    redirectTo: 'procesos',
    pathMatch: 'full',
  }, 
  {path:'kill', component:KillpComponent},
  {
    path: '',
    redirectTo: 'kill',
    pathMatch: 'full',
  },
  {
    path: '',
    component: AdminLayoutComponent,
    children: [
        {
      path: '',
      loadChildren: './layouts/admin-layout/admin-layout.module#AdminLayoutModule'
  }]},
  {
    path: '**',
    redirectTo: 'dashboard'
  }
];

@NgModule({
  imports: [
    CommonModule,
    BrowserModule,
    RouterModule.forRoot(routes)
  ],
  exports: [
  ],
})
export class AppRoutingModule { }
