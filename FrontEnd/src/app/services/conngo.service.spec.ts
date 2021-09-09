import { TestBed } from '@angular/core/testing';

import { ConngoService } from './conngo.service';

describe('ConngoService', () => {
  let service: ConngoService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(ConngoService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
