#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/mm.h>

MODULE_LICENSE("P1");
MODULE_AUTHOR("MIGUEL ANGEL");
MODULE_DESCRIPTION("Modulo que muestra la los procesos");
MODULE_VERSION("1");

struct task_struct *task; //Estructura definida en sched.h para tareas/procesos
struct task_struct *childtask; //Estructura necesaria para iterar a travez de procesos secundarios
struct task_struct *memtask; 
struct list_head *list; //Estructura necesaria para recorrer cada lista de tareas tarea->estructura de hijos
struct sysinfo inf;

static int write_cpu(struct seq_file * cpufile, void *v){
	unsigned long rss;
	si_meminfo(&inf);

	int p = 0;

	int tot = 0;
	int eje = 0;
	int sus = 0;
	int det = 0;
	int zom = 0;
	
	seq_printf(cpufile, "{\n\"procesos\":[\n");
	for_each_process( task ){
		get_task_struct(task);

		if(p == 0){
			p = 1;
		}else if(p == 1){
			seq_printf(cpufile, "},\n");
		}

		tot++;
		if(task->state == 0){
			eje++;
		}else if(task->state == 1 || task->state == 2){
			sus++;
		}else if(task->state == 4){
			det++;
		}else if(task->exit_state == 32){
			zom++;
		}

		seq_printf(cpufile, "{\n");
		seq_printf(cpufile, "\"pid\": %d,\n",task->pid);
		seq_printf(cpufile, "\"nombre\": \"%s\",\n",task->comm);
		seq_printf(cpufile, "\"estado\": %ld,\n",task->state);
		if (task->mm) {
            rss = get_mm_rss(task->mm) << PAGE_SHIFT;
			seq_printf(cpufile, "\"uso\": %lu,\n", rss/(1024));
			seq_printf(cpufile, "\"total\": %lu,\n", (inf.totalram * 4));
        } else {
			rss = 0;
			seq_printf(cpufile, "\"uso\": %lu,\n", rss);
			seq_printf(cpufile, "\"total\": %lu,\n", (inf.totalram * 4));
        }
		seq_printf(cpufile, "\"mem\": %lu,\n", task->usage);
		seq_printf(cpufile, "\"usuario\": \"%d\",\n", __kuid_val(task_uid(task)));
		seq_printf(cpufile, "\"hijo\":\n");
		seq_printf(cpufile, "\t[\n");

		int p2 = 0;
		list_for_each( list,&task->children ){
			if(p2 == 0){
				p2 = 1;
			}else if(p2 == 1){
				seq_printf(cpufile, "\t},\n");
			}

			tot++;
			if(task->state == 0){
				eje++;
			}else if(task->state == 1 || task->state == 2){
				sus++;
			}else if(task->state == 4){
				det++;
			}else if(task->exit_state == 32){
				zom++;
			}

			seq_printf(cpufile, "\t{\n");
			childtask= list_entry( list, struct task_struct, sibling );
			
			seq_printf(cpufile, "\t\"pid\": %d,\n",childtask->pid);
			seq_printf(cpufile, "\t\"nombre\": \"%s\"\n",childtask->comm);
			//seq_printf(cpufile, "\t\"padre\": %d,\n",task->pid);
			//seq_printf(cpufile, "\t\"estado\": %ld,\n",childtask->state);
			//seq_printf(cpufile, "\t\"uso\": %ld\n",childtask->usage);
			
		}

		if(p2 == 1){
			seq_printf(cpufile, "\t}\n");
		}
		seq_printf(cpufile, "\t]\n");
		

        //put_task_struct(task);
	}

	seq_printf(cpufile, "}\n");
	seq_printf(cpufile, "],\n");
	seq_printf(cpufile, "\"datos\":{\n");
	seq_printf(cpufile, "\"total\": %i,\n", tot);
	seq_printf(cpufile, "\"ejecucion\": %i,\n", eje);
	seq_printf(cpufile, "\"suspendido\": %i,\n", sus);
	seq_printf(cpufile, "\"detenido\": %i,\n", det);
	seq_printf(cpufile, "\"zombie\": %i\n", zom);
	seq_printf(cpufile, "}\n");
	seq_printf(cpufile, "}");

	return 0;
}

static int my_proc_open(struct inode *inode, struct file*file){
	return single_open(file, write_cpu, NULL);	
}

static ssize_t my_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos){
    return 0;
}

static struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_proc_open,
    .release = single_release,
    .read = seq_read,
    .llseek = seq_lseek,
    .write = my_proc_write
};

static int __init cpu_mod_init(void){ //modulo de inicio
	printk(KERN_INFO "cpu_p1: lectura de cpu iniciado");
    proc_create("cpu_p1", 0, NULL, &my_fops);
	
    return 0;
}

static void __exit cpu_mod_exit(void){
	printk(KERN_INFO "cpu_p1: lectura de cpu finalizado");
	remove_proc_entry("cpu_p1", NULL);
}

module_init(cpu_mod_init);
module_exit(cpu_mod_exit);