import { ComponentFixture, TestBed } from '@angular/core/testing';

import { KillpComponent } from './killp.component';

describe('KillpComponent', () => {
  let component: KillpComponent;
  let fixture: ComponentFixture<KillpComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ KillpComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(KillpComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
