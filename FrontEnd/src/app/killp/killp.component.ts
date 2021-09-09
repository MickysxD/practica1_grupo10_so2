import { Component, OnInit } from '@angular/core';
import { ConngoService } from '../services/conngo.service';

@Component({
  selector: 'app-killp',
  templateUrl: './killp.component.html',
  styleUrls: ['./killp.component.css']
})
export class KillpComponent implements OnInit {

  constructor(private conngo: ConngoService) { }

  ngOnInit(): void {
  }

  kill(_id:any){
    if(_id == ""){
      alert("inserte un id")
      return
    }
    let ki = this.conngo.kill({id:parseInt(_id)})
    ki.subscribe(res=>{
        let resultado = JSON.parse(JSON.stringify(res))
        console.log(resultado.Result)
    })
  }

}
