import { Component, OnInit } from '@angular/core';
import { ConngoService } from '../services/conngo.service';

@Component({
  selector: 'app-procesos',
  templateUrl: './procesos.component.html',
  styleUrls: ['./procesos.component.css']
})
export class ProcesosComponent implements OnInit {

  constructor(private conngo: ConngoService) { 
    this.cargar_procesos()
  }

  ngOnInit(): void {
  }
  cpu:any
  procesos:any
  procesos_hijo:any = []
  es_hijo:any = 0
  cargar_procesos(){
    (async () => {
      while(this.es_hijo == 0) { 
      // Do something before delay
        // Do something after
        let con = this.conngo.procesos()
        con.subscribe(res=>{
          if(this.es_hijo == 0){
            this.cpu = JSON.parse(JSON.stringify(res))
            this.procesos = this.cpu.Procesos
            console.log(this.es_hijo )
      
            console.log(this.cpu)
          }
        })
        await this.delay(3000);
        
      }
    })();
    
  }
  delay(ms: number) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }

  ver_hijos(hijos:any){
    this.es_hijo = 1
    this.procesos_hijo = hijos
  }
  regresar(){
    this.es_hijo = 0;
    this.procesos_hijo = []
    this.cargar_procesos()
  }

}
